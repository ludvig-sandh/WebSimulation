#include "sceneClass.h"
#include <iostream>
#include <cassert>

Scene::Scene(GLFWwindow* window, int rows, int cols) {
	this->window = window;

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

void Scene::CreateGrid() {
	float width = 1.0f / this->cols * 1.5;
	float height = 1.0f / this->rows * 1.5;
	float ygap = 2.0f / (this->rows + 1);
	float xgap = 2.0f / (this->cols + 1);
	for (int row = 0; row < this->rows; row++) {
		float y = -1.0f + ygap * (row + 1);
		for (int col = 0; col < this->cols; col++) {
			float x = -1.0f + xgap * (col + 1);
			size_t index = this->GetGridIndex(row, col);

			SceneObject object;
			object.geometry = new SceneGeometryRect(x, y, width, height, 0.3f, 0.3f, 1.0f);

			// Now let's connect neighbours
			if (row) {
				int neighbourIndex = this->GetGridIndex(row - 1, col);
				this->objects[neighbourIndex].AddNeighbour(index);
				object.AddNeighbour(neighbourIndex);
			}
			else {
				// Add static edge point above
				object.AddStaticNeighbour(x, y - ygap);
			}
			if (row == this->rows - 1) {
				// Add static edge point below
				object.AddStaticNeighbour(x, y + ygap);
			}

			if (col) {
				int neighbourIndex = this->GetGridIndex(row, col - 1);
				this->objects[neighbourIndex].AddNeighbour(index);
				object.AddNeighbour(neighbourIndex);
			}
			else {
				// Add static edge point to left
				object.AddStaticNeighbour(x - xgap, y);
			}
			if (col == this->cols - 1) {
				// Add static edge point to right
				object.AddStaticNeighbour(x + xgap, y);
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
			float dx = this->mouseX - this->lastMouseX;
			float dy = this->mouseY - this->lastMouseY;
			object.geometry->TranslatePosition(dx, dy);

			this->lastMouseX = this->mouseX;
			this->lastMouseY = this->mouseY;
		}else {
			object.UpdateGeometry(this->objects);
		}

		// Change color based on how far from start each object is
		float color1;
		float color2;

		float dx = object.geometry->x - object.geometry->startX;
		float dy = object.geometry->y - object.geometry->startY;
		float dist = pow(dx * dx + dy * dy, 0.5f);
		color1 = std::max(0.0f, std::min(1.0f, dist / 0.1f));

		dx = object.geometry->x - object.geometry->lastX;
		dy = object.geometry->y - object.geometry->lastY;
		dist = pow(dx * dx + dy * dy, 0.5f);
		color2 = std::max(0.0f, std::min(1.0f, dist / 0.005f));

		object.geometry->SetColor(color1, color2, 1.0f - color1);

		object.geometry->lastX = object.geometry->x;
		object.geometry->lastY = object.geometry->y;
	}
}

void Scene::BuildTriangles(GLfloat **vertexBuffer, GLuint **indexBuffer, 
						   size_t &vertexBufferSize, size_t &indexBufferSize) {
	vertexBufferSize = sizeof(GLfloat) * this->numVertices * 6;
	indexBufferSize = sizeof(GLuint) * this->numIndices * 3;
	*vertexBuffer = (GLfloat*)malloc(vertexBufferSize);
	*indexBuffer = (GLuint*)malloc(indexBufferSize);
	if (*vertexBuffer == NULL || *indexBuffer == NULL) {
		std::cout << "Malloc memory allocation failed." << std::endl;
		exit(0);
	}
	size_t vBufferIndex = 0, iBufferIndex = 0;

	for (size_t i = 0; i < this->numObjects; i++) {

		SceneObject object = this->objects[i];

		for (int val : object.geometry->indices) {
			(*indexBuffer)[iBufferIndex++] = (GLuint)(vBufferIndex / 6 + val);
		}

		for (float val : object.geometry->vertices) {
			assert(vBufferIndex < vertexBufferSize);
			(*vertexBuffer)[vBufferIndex++] = (GLfloat)(val);
		}
	}
}

void Scene::UpdateTriangles(GLfloat **vertexBuffer) {
	size_t vBufferIndex = 0;

	for (size_t i = 0; i < this->numObjects; i++) {
		SceneObject object = this->objects[i];

		for (float val : object.geometry->vertices) {
			(*vertexBuffer)[vBufferIndex++] = (GLfloat)(val);
		}
	}
}

void Scene::Destroy(GLfloat* vertexBuffer, GLuint* indexBuffer) {
	free(vertexBuffer);
	free(indexBuffer);
}

void Scene::MousePressed(double x, double y) {
	this->mouseX = x;
	this->mouseY = y;
	if (this->isMousePressed) return;
	this->isMousePressed = true;
	this->lastMouseX = x;
	this->lastMouseY = y;

	for (SceneObject& object : this->objects) {
		// Check if this object is currently being dragged by user
		if (object.geometry->Contains(x, y)) {
			// Set static state for this object
			object.isStatic = true;
		}
	}
}

void Scene::MouseReleased(double x, double y) {
	this->mouseX = x;
	this->mouseY = y;
	if (!this->isMousePressed) return;
	this->isMousePressed = false;

	// If an object was dragged before, let it move freely now
	for (SceneObject& object : this->objects) {
		object.isStatic = false;
	}
}