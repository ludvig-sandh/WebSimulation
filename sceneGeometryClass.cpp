#include "sceneGeometryClass.h"

// Translates the position of a scene geometry object
void SceneGeometry::TranslatePosition(float dx, float dy) {
	this->x += dx;
	this->y += dy;
	// Loop through all vertices and update their x & y coordinates
	for (size_t i = 0; i < vertices.size(); i += 6) {
		vertices[i] += dx;
		vertices[i + 1] += dy;
	}
}

SceneGeometryRect::SceneGeometryRect(float x, float y, float width, float height,
	float red, float green, float blue, float alpha) {
	// Store instance variables
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	// Create vertices for four corners of rectangle
	this->vertices = {
		x - width / 2.0f, y - height / 2.0f, 0.0f, red, green, blue,
		x + width / 2.0f, y - height / 2.0f, 0.0f, red, green, blue,
		x + width / 2.0f, y + height / 2.0f, 0.0f, red, green, blue,
		x - width / 2.0f, y + height / 2.0f, 0.0f, red, green, blue,
	};

	// Split rectangle diagonally into two triangles
	this->indices = {
		0, 1, 2,
		2, 3, 0
	};

	this->numVertices = this->vertices.size() / 6;
	this->numIndices = this->indices.size() / 3;
}

bool SceneGeometryRect::Contains(float xOther, float yOther) {
	if (std::abs(xOther - this->x) > this->width / 2) return false;
	if (std::abs(yOther - this->y) > this->height / 2) return false;
	return true;
}