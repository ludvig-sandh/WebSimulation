#define _USE_MATH_DEFINES

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

void SceneObject::SetRotation(float angle) {
    m_angle = angle;
}

void SceneObject::SetScale(const Vec2 scale) {
    m_scale = scale;
}

void SceneObject::SetScale(const float scale) {
    m_scale = Vec2(scale, scale);
}

std::vector<float> SceneObject::GetVertices() const {
    std::vector<float> vertices;
    vertices.reserve(m_points.size() * 6);
    for (const Vec2 &point : m_points) {
        Vec2 transformed = point.rotate(m_angle) * m_scale;
        vertices.insert(vertices.end(), {transformed.x + position.x, transformed.y + position.y, zIndex, color.x, color.y, color.z});
    }
    return vertices;
}

SceneRect::SceneRect(const Vec2 position, const Vec2 size, float red, float green, float blue)
    : SceneObject(position), m_size(size) {
    color = Vec3(red, green, blue);

	// Create vertices for four corners of rectangle
    m_points = {
		Vec2(-m_size.x / 2.0f, - m_size.y / 2.0f),
		Vec2(+m_size.x / 2.0f, - m_size.y / 2.0f),
		Vec2(+m_size.x / 2.0f, + m_size.y / 2.0f),
		Vec2(-m_size.x / 2.0f, + m_size.y / 2.0f)
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
    Vec2 transformed = ((point - position) / m_scale).rotate(-m_angle);
    return std::abs(transformed.x) <= m_size.x / 2 && std::abs(transformed.y) <= m_size.y / 2;
}

SceneConvexPolygon::SceneConvexPolygon(const Vec2 position, const std::vector<Vec2> points, float red, float green, float blue)
    : SceneObject(position) {
    color = Vec3(red, green, blue);
    m_points = points;

    int minIndex = std::distance(m_points.begin(), std::min_element(m_points.begin(), m_points.end()));

    int topIndex = minIndex;
    int bottomIndex = minIndex;

    // minIndex is always the leftmost point. In case of multiple leftmost points, it is the bottom one.
    // So loop through the points in counterclockwise order and find the topmost point that is still a leftmost one.
    float lastX = m_points[topIndex].x;
    while (true) {
        int nextTopIndex = (topIndex + m_points.size() - 1) % m_points.size();
        if (m_points[nextTopIndex].x == lastX) {
            topIndex = nextTopIndex;
        }else {
            break;
        }
        lastX = m_points[topIndex].x;
    }

    // Push all points on the top part of the hull until we reach the rightmost point.
    do {
        m_topVertices.push_back(m_points[topIndex]);
        lastX = m_points[topIndex].x;
        topIndex = (topIndex + m_points.size() - 1) % m_points.size();
    }while (m_points[topIndex].x > lastX);

    // Push all points on the bottom part of the hull until we reach the rightmost point.
    do {
        m_bottomVertices.push_back(m_points[bottomIndex]);
        lastX = m_points[bottomIndex].x;
        bottomIndex = (bottomIndex + 1) % m_points.size();
    }while (m_points[bottomIndex].x > lastX);

    assert(m_topVertices.back().x == m_bottomVertices.back().x);
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
    Vec2 transformed = ((point - position) / m_scale).rotate(-m_angle);

    // Point is to the left of the entire polygon
    if (transformed.x < m_topVertices.front().x)
        return false;

    if (transformed.x > m_topVertices.back().x)
        return false;

    if (transformed.x == m_topVertices.front().x)
        return transformed.y <= m_topVertices.front().y && transformed.y >= m_bottomVertices.front().y;

    if (transformed.x == m_topVertices.back().x)
        return transformed.y <= m_topVertices.back().y && transformed.y >= m_bottomVertices.back().y;

    int indexFirstElementGreater = std::distance(m_topVertices.begin(), std::upper_bound(m_topVertices.begin(), m_topVertices.end(), transformed));
    Vec2 rightPoint = m_topVertices[indexFirstElementGreater];
    Vec2 leftPoint = m_topVertices[indexFirstElementGreater - 1];
    if (transformed.x < leftPoint.x) {
        assert(transformed.x >= leftPoint.x);
    }
    assert(transformed.x <= rightPoint.x);
    float slopeBetweenPoints = (rightPoint.y - leftPoint.y) / (rightPoint.x - leftPoint.x);
    float maxYHeight = (transformed.x - leftPoint.x) * slopeBetweenPoints + leftPoint.y;
    if (transformed.y > maxYHeight)
        return false;
    
    indexFirstElementGreater = std::distance(m_bottomVertices.begin(), std::upper_bound(m_bottomVertices.begin(), m_bottomVertices.end(), transformed));
    rightPoint = m_bottomVertices[indexFirstElementGreater];
    leftPoint = m_bottomVertices[indexFirstElementGreater - 1];
    assert(transformed.x >= leftPoint.x);
    assert(transformed.x <= rightPoint.x);
    slopeBetweenPoints = (rightPoint.y - leftPoint.y) / (rightPoint.x - leftPoint.x);
    float minYHeight = (transformed.x - leftPoint.x) * slopeBetweenPoints + leftPoint.y;
    if (transformed.y < minYHeight)
        return false;
    
    return true;
}

SceneCircle::SceneCircle(const Vec2 position, float radius, float red, float green, float blue)
    : SceneObject(position), m_radius(radius) {
    color = Vec3(red, green, blue);

    InitCircle(radius, 30);
}

SceneCircle::SceneCircle(const Vec2 position, float radius, float red, float green, float blue, int resolution)
    : SceneObject(position), m_radius(radius) {
    color = Vec3(red, green, blue);

    if (resolution < 3) {
        throw std::runtime_error("ERROR: Cannot create a circle with less than 3 points");
    }
    InitCircle(radius, resolution);
}

std::vector<int> SceneCircle::GetIndices() const {
    std::vector<int> indices;
    // For a convex polygon with N corners, we can draw it with N-2 triangles
    indices.reserve((m_points.size() - 2) * 3);
    for (int i = 1; i < (int)m_points.size() - 1; i++) {
        indices.insert(indices.end(), {0, i, i + 1});
    }
    return indices;
}

bool SceneCircle::Contains(const Vec2 &point) const {
    // Check if distance from circle center to point is less than the circle's radius
    Vec2 transformed = ((point - position) / m_scale).rotate(-m_angle);
    return transformed.abs() <= m_radius;
}

void SceneCircle::InitCircle(float radius, int resolution) {
    float angleBetweenPoints = 2.0 * M_PI / (float)resolution;
    for (int i = 0; i < resolution; i++) {
        m_points.emplace_back(radius * cos(angleBetweenPoints * i), radius * sin(angleBetweenPoints * i));
    }
}