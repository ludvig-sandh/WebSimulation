#include <cmath>

#include "SceneGeometry.h"
#include "Vec2.h"

// Translates the position of a scene geometry object
void SceneGeometry::TranslatePosition(const Vec2 &translation) {
    m_position += translation;

    // Loop through all vertices and update their x & y coordinates
	for (size_t i = 0; i < this->vertices.size(); i += 6) {
		this->vertices[i] += translation.x;
		this->vertices[i + 1] += translation.y;
	}
}

// Updates the color of the object
void SceneGeometry::SetColor(float red, float green, float blue) {
	for (size_t i = 0; i < 4; i++) {
		this->vertices[i * 6 + 3] = red;
		this->vertices[i * 6 + 4] = green;
		this->vertices[i * 6 + 5] = blue;
	}
}

SceneGeometryRect::SceneGeometryRect(const Vec2 &position, const Vec2 &size,
	float red, float green, float blue) {
	// Store instance variables
    m_position = position;
    m_lastPosition = position;
    m_startPosition = position;

    m_size = size;

	// Create vertices for four corners of rectangle
	this->vertices = {
		position.x - size.x / 2.0f, position.y - size.y / 2.0f, 0.0f, red, green, blue,
		position.x + size.x / 2.0f, position.y - size.y / 2.0f, 0.0f, red, green, blue,
		position.x + size.x / 2.0f, position.y + size.y / 2.0f, 0.0f, red, green, blue,
		position.x - size.x / 2.0f, position.y + size.y / 2.0f, 0.0f, red, green, blue,
	};

	// Split rectangle diagonally into two triangles
	this->indices = {
		0, 1, 2,
		2, 3, 0
	};

	this->numVertices = this->vertices.size() / 6;
	this->numIndices = this->indices.size() / 3;
}

bool SceneGeometryRect::Contains(const Vec2 &point) {
	if (std::abs(point.x - m_position.x) > m_size.x / 2) return false;
	if (std::abs(point.y - m_position.y) > m_size.y / 2) return false;
	return true;
}