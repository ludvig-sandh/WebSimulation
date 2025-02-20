#include "SceneObject.h"
#include "Vec2.h"
#include "Vec3.h"

#include <cmath>

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

