#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "SceneObject.h"
#include "Vec2.h"
#include "Vec3.h"

SceneObject::SceneObject(Vec2 position) : position(position) {}

// Updates the color of the object
void SceneObject::SetColor(float red, float green, float blue) {
    color = Vec3(red, green, blue);
}

SceneRect::SceneRect(const Vec2 position, const Vec2 size, float red, float green, float blue)
    : SceneObject(position), m_size(size) {
    color = Vec3(red, green, blue);
}

std::vector<float> SceneRect::GetVertices() const {
	// Create vertices for four corners of rectangle
    return {
		position.x - m_size.x / 2.0f, position.y - m_size.y / 2.0f, zIndex, color.x, color.y, color.z,
		position.x + m_size.x / 2.0f, position.y - m_size.y / 2.0f, zIndex, color.x, color.y, color.z,
		position.x + m_size.x / 2.0f, position.y + m_size.y / 2.0f, zIndex, color.x, color.y, color.z,
		position.x - m_size.x / 2.0f, position.y + m_size.y / 2.0f, zIndex, color.x, color.y, color.z,
	};
}

std::vector<int> SceneRect::GetIndices() const {
	// Split rectangle diagonally into two triangles
	return {
		0, 1, 2,
		2, 3, 0
	};
}

bool SceneRect::Contains(const Vec2 &point) const {
	if (std::abs(point.x - position.x) > m_size.x / 2) return false;
	if (std::abs(point.y - position.y) > m_size.y / 2) return false;
	return true;
}

SceneConvexPolygon::SceneConvexPolygon(const std::vector<Vec2> &points, float red, float green, float blue)
    : SceneObject(position), m_points(points) {
    color = Vec3(red, green, blue);

    int minIndex = std::distance(m_points.begin(), std::min_element(m_points.begin(), m_points.end()));

    int topIndex = minIndex;
    int bottomIndex = minIndex;
    float lastX;
    do {
        m_topVertices.push_back(m_points[topIndex]);
        lastX = m_points[topIndex].x;
        topIndex = (topIndex - 1) % m_points.size();
    }while (m_points[topIndex].x > lastX);
    do {
        m_bottomVertices.push_back(m_points[bottomIndex]);
        lastX = m_points[bottomIndex].x;
        bottomIndex = (bottomIndex + 1) % m_points.size();
    }while (m_points[bottomIndex].x > lastX);

    assert(m_topVertices.back().x == m_bottomVertices.back().x);
}

std::vector<float> SceneConvexPolygon::GetVertices() const {
    std::vector<float> vertices;
    vertices.reserve(m_points.size() * 6);
    for (const Vec2 &point : m_points) {
        vertices.insert(vertices.end(), {point.x, point.y, zIndex, color.x, color.y, color.z});
    }
    return vertices;
}

std::vector<int> SceneConvexPolygon::GetIndices() const {
    std::vector<int> indices;
    // For a convex polygon with N corners, we can draw it with N-2 triangles
    indices.reserve((m_points.size() - 2) * 3);
    for (int i = 1; i < (int)m_points.size() - 1; i++) {
        indices.insert(indices.end(), {0, i, i + 1});
    }
    return indices;
}

// Point in convex polygon checking algorithm
bool SceneConvexPolygon::Contains(const Vec2 &point) const {
    // Point is to the left of the entire polygon
    if (point.x < m_topVertices.front().x)
        return false;

    if (point.x > m_topVertices.back().x)
        return false;

    int indexFirstElementGreater = std::distance(m_topVertices.begin(), std::upper_bound(m_topVertices.begin(), m_topVertices.end(), point));
    indexFirstElementGreater = std::min(indexFirstElementGreater, (int)m_topVertices.size() - 1);
    Vec2 rightPoint = m_topVertices[indexFirstElementGreater];
    Vec2 leftPoint = m_topVertices[indexFirstElementGreater - 1];
    assert(point.x >= leftPoint.x);
    assert(point.x <= rightPoint.x);
    float slopeBetweenPoints = (rightPoint.y - leftPoint.y) / (rightPoint.x - leftPoint.x);
    float maxYHeight = (point.x - leftPoint.x) * slopeBetweenPoints + leftPoint.y;
    if (point.y > maxYHeight)
        return false;
    
    indexFirstElementGreater = std::distance(m_bottomVertices.begin(), std::upper_bound(m_bottomVertices.begin(), m_bottomVertices.end(), point));
    indexFirstElementGreater = std::min(indexFirstElementGreater, (int)m_bottomVertices.size() - 1);
    rightPoint = m_bottomVertices[indexFirstElementGreater];
    leftPoint = m_bottomVertices[indexFirstElementGreater - 1];
    assert(point.x >= leftPoint.x);
    assert(point.x <= rightPoint.x);
    slopeBetweenPoints = (rightPoint.y - leftPoint.y) / (rightPoint.x - leftPoint.x);
    float minYHeight = (point.x - leftPoint.x) * slopeBetweenPoints + leftPoint.y;
    if (point.y < minYHeight)
        return false;
    
    return true;
}