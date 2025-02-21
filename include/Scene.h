#pragma once

#include <memory>

#include "GLFW/glfw3.h"
#include "SceneObject.h"
#include "Vec2.h"

class Scene {
public:
	virtual void Update(float timeDelta) = 0;
	void ComputeTriangles();
    GLfloat *getVertexBuffer();
    GLuint *getIndexBuffer();
    int getVertexBufferCount();
    int getIndexBufferCount();

	virtual void MousePressed(Vec2 mouseLocation) = 0;
	virtual void MouseReleased(Vec2 mouseLocation) = 0;
private:
    // Contains all vertices, and all vertex indices of triangles
    std::vector<GLfloat> m_vertexBuffer; // X, Y, Z, R, G, B repeating for each vertex
    std::vector<GLuint> m_indexBuffer; // v0, v1, v2 (for a triangle) repeating for each triangle

    std::vector<std::shared_ptr<SceneObject>> m_objects;
protected:
    int width, height;
    void AddObject(std::shared_ptr<SceneObject> object);
    void RemoveObject(std::shared_ptr<SceneObject> object);
};