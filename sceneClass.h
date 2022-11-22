#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <GLFW/glfw3.h>

class Scene {
public:

	Scene(GLFWwindow window);
	void Update();
	void BuildTriangles(GLfloat* vertexBuffer, GLuint* indexBuffer);
};


#endif