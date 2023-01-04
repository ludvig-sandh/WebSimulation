#include "sceneGeometryClass.h"

// Translates the position of a scene geometry object
void SceneGeometry::TranslatePosition(float dx, float dy) {
	this->x += dx;
	this->y += dy;
}

// Updates the color of the object
void SceneGeometry::SetColor(float red, float green, float blue) {
	this->vertices[3] = red;
	this->vertices[4] = green;
	this->vertices[5] = blue;
}

SceneGeometryRect::SceneGeometryRect(float x, float y, float width, float height,
	float red, float green, float blue) {
	// Store instance variables
	this->x = x;
	this->y = y;
	this->lastX = x;
	this->lastY = y;
	this->startX = x;
	this->startY = y;

	this->width = width;
	this->height = height;

	// Create vertices for four corners of rectangle
	this->vertices = {
		x, y, 0.0f, red, green, blue
	};

	this->numVertices = 1;
}

bool SceneGeometryRect::Contains(float xOther, float yOther) {
	if (std::abs(xOther - this->x) > this->width / 2) return false;
	if (std::abs(yOther - this->y) > this->height / 2) return false;
	return true;
}