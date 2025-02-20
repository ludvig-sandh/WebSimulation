#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <memory>
#include <GLFW/glfw3.h>

#include "SceneObject.h"
#include "Vec2.h"

class Scene {
public:
	Scene();
    
	void Update();
	void ComputeTriangles();
    GLfloat *getVertexBuffer();
    GLuint *getIndexBuffer();
    int getVertexBufferCount();
    int getIndexBufferCount();

	void MousePressed(Vec2 mouseLocation);
	void MouseReleased(Vec2 mouseLocation);
private:
    // Contains all vertices, and all vertex indices of triangles
    std::vector<GLfloat> m_vertexBuffer; // X, Y, Z, R, G, B repeating for each vertex
    std::vector<GLuint> m_indexBuffer; // v0, v1, v2 (for a triangle) repeating for each triangle

    int width, height;
    std::vector<std::unique_ptr<SceneObject>> m_objects;
};

#endif