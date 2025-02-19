#include "Scene.h"

#include <iostream>
#include <cassert>
#include <cmath>

Scene::Scene(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	this->numObjects = rows * cols;

	this->CreateGrid();

	// Now when the creator has added all objects, count all
	// vertices and indices in the scene
	for (SceneObject& object : this->objects) {
		this->numVertices += object.geometry->numVertices;
		this->numIndices += object.geometry->numIndices;
	}
}

// Deletes the memory allocated vertices and indices pointers
Scene::~Scene() {
	free(this->vertexBuffer);
	free(this->indexBuffer);
}

void Scene::CreateGrid() {
    Vec2 size, position;
	size.x = 1.0f / this->cols * 1.5;
	size.y = 1.0f / this->rows * 1.5;
	float ygap = 2.0f / (this->rows + 1);
	float xgap = 2.0f / (this->cols + 1);
	for (int row = 0; row < this->rows; row++) {
		position.y = -1.0f + ygap * (row + 1);
		for (int col = 0; col < this->cols; col++) {
			position.x = -1.0f + xgap * (col + 1);
			size_t index = this->GetGridIndex(row, col);

			SceneObject object;
			object.geometry = new SceneGeometryRect(position, size, 0.3f, 0.3f, 1.0f);

			// Now let's connect neighbours
			if (row) {
				int neighbourIndex = this->GetGridIndex(row - 1, col);
				this->objects[neighbourIndex].AddNeighbour(index);
				object.AddNeighbour(neighbourIndex);
			}
			else {
				// Add static edge point above
				object.AddStaticNeighbour(Vec2(position.x, position.y - ygap));
			}
			if (row == this->rows - 1) {
				// Add static edge point below
				object.AddStaticNeighbour(Vec2(position.x, position.y + ygap));
			}

			if (col) {
				int neighbourIndex = this->GetGridIndex(row, col - 1);
				this->objects[neighbourIndex].AddNeighbour(index);
				object.AddNeighbour(neighbourIndex);
			}
			else {
				// Add static edge point to left
				object.AddStaticNeighbour(Vec2(position.x - xgap, position.y));
			}
			if (col == this->cols - 1) {
				// Add static edge point to right
				object.AddStaticNeighbour(Vec2(position.x + xgap, position.y));
			}

			this->objects.push_back(object);
		}
	}
}

int Scene::GetGridIndex(int row, int col) {
	return row * this->cols + col;
}

void Scene::Update() {
	for (SceneObject& object : this->objects) {
		// Check if this object is currently being dragged by user
		if (object.isStatic) {
            Vec2 translation = m_currentMouseLocation - m_lastMousePressedLocation;
			object.geometry->TranslatePosition(translation);

            m_lastMousePressedLocation = m_currentMouseLocation;
		}else {
			object.UpdateGeometry(this->objects);
		}

		// Change color based on how far from start each object is
		float color1;
		float color2;

		float dx = object.geometry->m_position.x - object.geometry->m_startPosition.x;
		float dy = object.geometry->m_position.y - object.geometry->m_startPosition.y;
		float dist = pow(dx * dx + dy * dy, 0.5f);
		color1 = std::max(0.0f, std::min(1.0f, dist / 0.1f));

		dx = object.geometry->m_position.x - object.geometry->m_lastPosition.x;
		dy = object.geometry->m_position.y - object.geometry->m_lastPosition.y;
		dist = pow(dx * dx + dy * dy, 0.5f);
		color2 = std::max(0.0f, std::min(1.0f, dist / 0.005f));

		object.geometry->SetColor(color1, color2, 1.0f - color1);

		object.geometry->m_lastPosition.x = object.geometry->m_position.x;
		object.geometry->m_lastPosition.y = object.geometry->m_position.y;
	}
}

void Scene::BuildTriangles() {
	this->vertexBufferSize = sizeof(GLfloat) * this->numVertices * 6;
	this->indexBufferSize = sizeof(GLuint) * this->numIndices * 3;
	this->vertexBuffer = (GLfloat*)malloc(vertexBufferSize);
	this->indexBuffer = (GLuint*)malloc(indexBufferSize);
	if (!this->vertexBuffer || !this->indexBuffer) {
		std::cout << "Malloc memory allocation failed." << std::endl;
		exit(0);
	}
	size_t vBufferIndex = 0, iBufferIndex = 0;

	for (size_t i = 0; i < this->numObjects; i++) {

		SceneObject object = this->objects[i];

		for (int val : object.geometry->indices) {
			this->indexBuffer[iBufferIndex++] = (GLuint)(vBufferIndex / 6 + val);
		}

		for (float val : object.geometry->vertices) {
			assert(vBufferIndex < vertexBufferSize);
			this->vertexBuffer[vBufferIndex++] = (GLfloat)(val);
		}
	}
}

void Scene::UpdateTriangles() {
	size_t vBufferIndex = 0;

	for (size_t i = 0; i < this->numObjects; i++) {
		SceneObject object = this->objects[i];

		for (float val : object.geometry->vertices) {
			this->vertexBuffer[vBufferIndex++] = (GLfloat)(val);
		}
	}
}


void Scene::MousePressed(Vec2 mouseLocation) {
    m_currentMouseLocation = mouseLocation;
	if (this->isMousePressed) return;
	this->isMousePressed = true;
    m_lastMousePressedLocation = mouseLocation;

	for (SceneObject& object : this->objects) {
		// Check if this object is currently being dragged by user
		if (object.geometry->Contains(mouseLocation)) {
			// Set static state for this object
			object.isStatic = true;
		}
	}
}

void Scene::MouseReleased(Vec2 mouseLocation) {
    m_currentMouseLocation = mouseLocation;
	if (!this->isMousePressed) return;
	this->isMousePressed = false;

	// If an object was dragged before, let it move freely now
	for (SceneObject& object : this->objects) {
		object.isStatic = false;
	}
}