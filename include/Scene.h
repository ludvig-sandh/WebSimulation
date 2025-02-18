#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <GLFW/glfw3.h>
#include "SceneObject.h"

class Scene {
public:
    // Contains all vertices, and all vertex indices of triangles
    GLfloat *vertexBuffer; // X, Y, Z, R, G, B repeating for each vertex
    GLuint *indexBuffer; // v0, v1, v2 (for a triangle) repeating for each triangle
    size_t vertexBufferSize, indexBufferSize;

	GLFWwindow *window;
	std::vector<SceneObject> objects;
	int rows, cols;
	size_t numVertices = 0, numIndices = 0, numObjects = 0;
	double mouseX = 0, mouseY = 0;
	double lastMouseX = 0, lastMouseY = 0;
	bool isMousePressed = false;

	Scene(GLFWwindow *window, int rows, int cols);
    ~Scene();

	void CreateGrid();
	int GetGridIndex(int row, int col);
	
	void Update();
	void BuildTriangles();
	void UpdateTriangles();

	void MousePressed(double x, double y);
	void MouseReleased(double x, double y);
};

#endif