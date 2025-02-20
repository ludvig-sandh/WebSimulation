#include "Scene.h"

#include <iostream>
#include <cassert>
#include <cmath>

Scene::Scene() {
    // Example code for some rectangles
    for (float x = -1.05f; x < 1.0f; x += 0.03f) {
        for (float y = -1.05f; y < 1.0f; y += 0.03f) {
            float red = fmod((x + y) * (x + y), 1.0f);
            float green = fmod((x - y) * (x + y), 1.0f);
            float blue = fmod((x - y) * (x - y), 1.0f);
            std::unique_ptr<SceneRect> rect = std::make_unique<SceneRect>(Vec2(x, y), Vec2(0.05, 0.05), red, green, blue);
            m_objects.push_back(std::move(rect));
        }
    }
}

void Scene::Update() {
    // Example code for some rectangles
    for (std::unique_ptr<SceneObject> &object : m_objects) {
        float dx = (0.5 - object->position.x - object->position.y) * (-object->position.x + object->position.y);
        float dy = (object->position.x + object->position.y) * (-0.5 - object->position.x + object->position.y);
        object->position += Vec2(dx * 0.0001, dy * 0.0001);
        if (object->position.x > 1.05) object->position.x -= 2.1;
        if (object->position.x < -1.05) object->position.x += 2.1;
        if (object->position.y > 1.05) object->position.y -= 2.1;
        if (object->position.y < -1.05) object->position.y += 2.1;
    }
}

void Scene::ComputeTriangles() {
    // TODO: Don't rebuild buffers every single frame.
	size_t vBufferIndex = 0;
    
    m_vertexBuffer.clear();
    m_indexBuffer.clear();

	for (size_t i = 0; i < m_objects.size(); i++) {
		for (int val : m_objects[i]->GetIndices()) {
            m_indexBuffer.push_back((GLuint)(vBufferIndex++ / 6 * 4 + val));
		}
		for (float val : m_objects[i]->GetVertices()) {
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

void Scene::MousePressed(Vec2 mouseLocation) {
    
}

void Scene::MouseReleased(Vec2 mouseLocation) {
    
}