#pragma once

#include <memory>
#include <set>

#include "GLFW/glfw3.h"
#include "SceneObject.h"
#include "Vec2.h"

class Scene {
public:
    Scene(Vec2 screenSize) : m_screenSize(screenSize) {};

	virtual void Update(float timeDelta) = 0;
	void ComputeTriangles();
    GLfloat *GetVertexBuffer();
    GLuint *GetIndexBuffer();
    int GetVertexBufferCount();
    int GetIndexBufferCount();

	virtual void MouseUpdate(Vec2 mouseLocation, bool isButtonDown) = 0;
private:
    // Contains all vertices, and all vertex indices of triangles
    std::vector<GLfloat> m_vertexBuffer; // X, Y, Z, R, G, B repeating for each vertex
    std::vector<GLuint> m_indexBuffer; // v0, v1, v2 (for a triangle) repeating for each triangle

    std::set<std::shared_ptr<SceneObject>, SceneObjectIdComparator> m_objects;
    int32_t m_largestId = -1;
protected:
    Vec2 m_screenSize;
    void AddObject(std::shared_ptr<SceneObject> object);
    void RemoveObject(const std::shared_ptr<SceneObject> &object);
};