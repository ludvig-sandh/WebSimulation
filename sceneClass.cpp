#include "sceneClass.h"
#include <iostream>
#include <cassert>

Scene::Scene(GLFWwindow* window, ObjectCreator *creator) {
	this->window = window;
	this->creator = creator;
	this->creator->Create(this->objects);

	// Now when the creator has added all objects, count all
	// vertices and indices in the scene
	for (size_t i = 0; i < this->creator->numObjects; i++) {
		this->numVertices += this->objects[i].geometry->numVertices;
		this->numIndices += this->objects[i].geometry->numIndices;
	}
}

void Scene::Update() {

}

void Scene::BuildTriangles(GLfloat* vertexBuffer, GLuint* indexBuffer) {
	size_t vertexBufferSize = sizeof(GLfloat) * this->numVertices * 6;
	size_t indexBufferSize = sizeof(GLuint) * this->numIndices * 3;
	vertexBuffer = (GLfloat*)malloc(vertexBufferSize);
	indexBuffer = (GLuint*)malloc(indexBufferSize);
	if (vertexBuffer == NULL || indexBuffer == NULL) {
		std::cout << "Malloc memory allocation failed." << std::endl;
		exit(0);
	}
	size_t vBufferIndex = 0, iBufferIndex = 0;

	for (size_t i = 0; i < this->creator->numObjects; i++) {
		SceneObject object = this->objects[i];
		for (size_t v = 0; v < object.geometry->numVertices * 6; v++) {
			assert(vBufferIndex < vertexBufferSize);
			vertexBuffer[vBufferIndex++] = object.geometry->vertices[v];
		}
	}
}

void UpdateTriangles(GLfloat* vertexBuffer) {
	
}