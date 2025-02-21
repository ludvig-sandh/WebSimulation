#include <iostream>
#include <cassert>

#include "Scene.h"

void Scene::ComputeTriangles() {
    // TODO: Don't rebuild buffers every single frame.
	int vertexCount = 0;
    
    m_vertexBuffer.clear();
    m_indexBuffer.clear();

	for (size_t i = 0; i < m_objects.size(); i++) {
		for (int val : m_objects[i]->GetIndices()) {
            m_indexBuffer.push_back((GLuint)(vertexCount + val));
		}
        std::vector<float> vertices = m_objects[i]->GetVertices();
        vertexCount += vertices.size() / 6;
		for (const float &val : vertices) {
            m_vertexBuffer.push_back((GLfloat)(val));
		}
	}
}

GLfloat *Scene::getVertexBuffer() {
    return this->m_vertexBuffer.data();
}

GLuint *Scene::getIndexBuffer() {
    return this->m_indexBuffer.data();
}

int Scene::getVertexBufferCount() {
    return this->m_vertexBuffer.size();
}

int Scene::getIndexBufferCount() {
    return this->m_indexBuffer.size();
}

void Scene::AddObject(std::shared_ptr<SceneObject> object) {
    m_objects.push_back(object);
}

// TODO: Implement RemoveObject. Instead of vector, use map or something so we can remove an object in O(1)
