#include <cmath>

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

bool SceneConvexPolygon::Contains(const Vec2 &point) const {
    // TODO: Implement point in convex polygon checking algorithm
    return true;
}