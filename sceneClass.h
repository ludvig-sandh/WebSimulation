#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <GLFW/glfw3.h>
#include "sceneObjectClass.h"
#include "objectCreatorClass.h"

class Scene {
public:
	GLFWwindow *window;
	std::vector<SceneObject> objects;
	ObjectCreator *creator;
	size_t numVertices = 0, numIndices = 0;

	Scene(GLFWwindow *window, ObjectCreator *creator);
	void Update();
	void BuildTriangles(GLfloat** vertexBuffer, GLuint** indexBuffer,
						size_t& vertexBufferSize, size_t& indexBufferSize);
	void UpdateTriangles(GLfloat **vertexBuffer);
	void Destroy(GLfloat* vertexBuffer, GLuint* indexBuffer);
};

#endif