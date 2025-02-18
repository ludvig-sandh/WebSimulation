#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <GLFW/glfw3.h>
#include "SceneObject.h"

class Scene {
public:

	GLFWwindow *window;
	std::vector<SceneObject> objects;
	int rows, cols;
	size_t numVertices = 0, numIndices = 0, numObjects = 0;
	double mouseX = 0, mouseY = 0;
	double lastMouseX = 0, lastMouseY = 0;
	bool isMousePressed = false;

	Scene(GLFWwindow *window, int rows, int cols);

	void CreateGrid();
	int GetGridIndex(int row, int col);
	
	void Update();
	void BuildTriangles(GLfloat** vertexBuffer, GLuint** indexBuffer,
						size_t& vertexBufferSize, size_t& indexBufferSize);
	void UpdateTriangles(GLfloat **vertexBuffer);
	void Destroy(GLfloat* vertexBuffer, GLuint* indexBuffer);

	void MousePressed(double x, double y);
	void MouseReleased(double x, double y);
};

#endif