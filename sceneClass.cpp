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

	for (size_t i = 0; i < this->creator->numObjects; i++) {
		SceneObject object = this->objects[i];

		for (int val : object.geometry->indices) {
			(*indexBuffer)[iBufferIndex++] = (GLuint)(vBufferIndex / 6 + val);
			std::printf("%d ", vBufferIndex / 6 + val);
		}
		std::printf("\n");

		for (float val : object.geometry->vertices) {
			assert(vBufferIndex < vertexBufferSize);
			(*vertexBuffer)[vBufferIndex++] = (GLfloat)(val);
			std::printf("%f ", val);
		}
		std::printf("\n");
		std::printf("\n");
	}
}

void Scene::UpdateTriangles(GLfloat* vertexBuffer) {
	
}

void Scene::Destroy(GLfloat* vertexBuffer, GLuint* indexBuffer) {
	free(vertexBuffer);
	free(indexBuffer);
}