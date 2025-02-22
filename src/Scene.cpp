#include <iostream>
#include <cassert>

#include "Scene.h"
#include "Vertex.h"

void Scene::ComputeTriangles() {
    // TODO: Don't rebuild buffers every single frame.
	int vertexCount = 0;
    
    m_vertexBuffer.clear();
    m_indexBuffer.clear();

    for (auto &object : m_objects) {
		for (int val : object->GetIndices()) {
            m_indexBuffer.push_back((GLuint)(vertexCount + val));
		}
        std::vector<Vertex> vertices = object->GetVertices();
        vertexCount += vertices.size();
		for (const Vertex &vertex : vertices) {
            m_vertexBuffer.push_back((GLfloat)(vertex.x / (float)m_screenSize.x * 2.0 - 1.0));
            m_vertexBuffer.push_back((GLfloat)(vertex.y / (float)m_screenSize.y * -2.0 + 1.0));
            m_vertexBuffer.push_back((GLfloat)(vertex.z));
            m_vertexBuffer.push_back((GLfloat)(vertex.r));
            m_vertexBuffer.push_back((GLfloat)(vertex.g));
            m_vertexBuffer.push_back((GLfloat)(vertex.b));
		}
	}
}

GLfloat *Scene::GetVertexBuffer() {
    return this->m_vertexBuffer.data();
}

GLuint *Scene::GetIndexBuffer() {
    return this->m_indexBuffer.data();
}

int Scene::GetVertexBufferCount() {
    return this->m_vertexBuffer.size();
}

int Scene::GetIndexBufferCount() {
    return this->m_indexBuffer.size();
}

void Scene::AddObject(std::shared_ptr<SceneObject> object) {
    object->id = ++m_largestId;
    m_objects.insert(object);
}

void Scene::RemoveObject(const std::shared_ptr<SceneObject> &object) {
    if (m_objects.find(object) != m_objects.end()) {
        m_objects.erase(object);
    }
}
