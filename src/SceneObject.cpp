#define _USE_MATH_DEFINES

#include <cmath>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "SceneObject.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vertex.h"

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

std::vector<Vertex> SceneObject::GetVertices() const {
    std::vector<Vertex> vertices;
    vertices.reserve(m_points.size() * 6);
    for (const Vec2 &point : m_points) {
        Vec2 transformed = point.rotate(m_angle) * m_scale;
        vertices.emplace_back(transformed.x + position.x, transformed.y + position.y, zIndex, color.x, color.y, color.z);
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

SceneConvexPolygon::SceneConvexPolygon(const Vec2 position, std::vector<Vec2> points, float red, float green, float blue)
    : SceneObject(position) {
    color = Vec3(red, green, blue);

    // First check that the points are convex
    if (!CheckConcavity(points)) {
        // They were not convex, check if they are if we reverse the order?
        // (maybe the user accidentally inserted the points in clockwise order)
        std::reverse(points.begin(), points.end());
        if (!CheckConcavity(points)) {
            // Nope, that was not the case either.
            throw std::runtime_error("ERROR: Cannot create convex polygon from a list of points that are not convex.");
        }
        
        std::cout << "WARNING: The set of points for creating a convex polygon were "
        "provided in clockwise order but should be provided in counterclockwise order." << std::endl;
    }

    // Find duplicate points
    std::set<Vec2> pointsSet;
    std::vector<Vec2> uniquePoints;
    for (auto &point : points) {
        if (pointsSet.find(point) != pointsSet.end()) {
            std::cout << "WARNING: The set of points for creating a convex polygon had duplicates, that were removed." << std::endl;
        }else {
            pointsSet.insert(point);
            uniquePoints.push_back(point);
        }
    }

    // If all points were unique, they are just added normally.
    m_points = uniquePoints;

    // Now that we know that the points should be valid, find the top and bottom part of the convex hull.
    BuildTopAndBottomHulls();
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
    if (transformed.x < m_topHull.front().x)
        return false;

    if (transformed.x > m_topHull.back().x)
        return false;

    if (transformed.y > m_maxY || transformed.y < m_minY)
        return false;

    if (transformed.x == m_topHull.front().x)
        return transformed.y <= m_topHull.front().y && transformed.y >= m_bottomHull.front().y;

    if (transformed.x == m_topHull.back().x)
        return transformed.y <= m_topHull.back().y && transformed.y >= m_bottomHull.back().y;

    int indexFirstElementGreater = std::distance(m_topHull.begin(), std::upper_bound(m_topHull.begin(), m_topHull.end(), transformed));
    Vec2 rightPoint = m_topHull[indexFirstElementGreater];
    Vec2 leftPoint = m_topHull[indexFirstElementGreater - 1];
    assert(transformed.x >= leftPoint.x);
    assert(transformed.x <= rightPoint.x);
    float slopeBetweenPoints = (rightPoint.y - leftPoint.y) / (rightPoint.x - leftPoint.x);
    float maxYHeight = (transformed.x - leftPoint.x) * slopeBetweenPoints + leftPoint.y;
    if (transformed.y > maxYHeight)
        return false;
    
    indexFirstElementGreater = std::distance(m_bottomHull.begin(), std::upper_bound(m_bottomHull.begin(), m_bottomHull.end(), transformed));
    rightPoint = m_bottomHull[indexFirstElementGreater];
    leftPoint = m_bottomHull[indexFirstElementGreater - 1];
    assert(transformed.x >= leftPoint.x);
    assert(transformed.x <= rightPoint.x);
    slopeBetweenPoints = (rightPoint.y - leftPoint.y) / (rightPoint.x - leftPoint.x);
    float minYHeight = (transformed.x - leftPoint.x) * slopeBetweenPoints + leftPoint.y;
    if (transformed.y < minYHeight)
        return false;
    
    return true;
}

// Tests a list of points representing points of a convex polygon in clockwise order to see if the polygon is concave.
bool SceneConvexPolygon::CheckConcavity(std::vector<Vec2> points) {
    for (size_t i = 0; i < points.size(); i++) {
        size_t nextIndex = (i + 1) % points.size();
        size_t nextNextIndex = (i + 2) % points.size();
        Vec2 a = points[i], b = points[nextIndex], c = points[nextNextIndex];
        
        // Check that a, b and c are in counterclockwise order
        if (a.x == b.x) {
            // If a and b are on a vertical line, check that c is on the right side
            if (a.y < b.y) {
                if (c.x > a.x) return false;
                continue;
            }

            if (c.x < a.x) return false;
            continue;
        }
        
        float k = (b.y - a.y) / (b.x - a.x);
        float threshold = a.y + k * (c.x - a.x);
        if (a.x < b.x) {
            // If a is left of b, check that c is above line created by a and b
            if (c.y < threshold) return false;
            continue;
        }

        // If a is right of b, check that c is below line created by a and b
        if (c.y > threshold) return false;
    }
    return true;
}

void SceneConvexPolygon::BuildTopAndBottomHulls() {
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
        m_maxY = std::max(m_maxY, m_points[topIndex].y);
        m_topHull.push_back(m_points[topIndex]);
        lastX = m_points[topIndex].x;
        topIndex = (topIndex + m_points.size() - 1) % m_points.size();
    }while (m_points[topIndex].x > lastX);
    
    // Push all points on the bottom part of the hull until we reach the rightmost point.
    do {
        m_minY = std::min(m_minY, m_points[bottomIndex].y);
        m_bottomHull.push_back(m_points[bottomIndex]);
        lastX = m_points[bottomIndex].x;
        bottomIndex = (bottomIndex + 1) % m_points.size();
    }while (m_points[bottomIndex].x > lastX);

    assert(m_topHull.back().x == m_bottomHull.back().x);
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