#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "MyScene.h"

MyScene::MyScene() {
    // Example code for some rectangles
    for (float x = -1.05f; x < 1.0f; x += 0.03f) {
        for (float y = -1.05f; y < 1.0f; y += 0.03f) {
            float red = fmod((x + y) * (x + y), 1.0f);
            float green = fmod((x - y) * (x + y), 1.0f);
            float blue = fmod((x - y) * (x - y), 1.0f);
            std::shared_ptr<SceneRect> rect = std::make_shared<SceneRect>(Vec2(x, y), Vec2(0.05, 0.05), red, green, blue);
            m_rects.push_back(rect);
            AddObject(rect);
        }
    }
}

void MyScene::Update(float timeDelta) {
    // Example code for some rectangles
    for (auto &rect : m_rects) {
        float dx = (0.5 - rect->position.x - rect->position.y) * (-rect->position.x + rect->position.y);
        float dy = (rect->position.x + rect->position.y) * (-0.5 - rect->position.x + rect->position.y);
        
        rect->position += Vec2(dx * 0.1, dy * 0.1) * timeDelta;
        if (rect->position.x > 1.05) rect->position.x -= 2.1;
        if (rect->position.x < -1.05) rect->position.x += 2.1;
        if (rect->position.y > 1.05) rect->position.y -= 2.1;
        if (rect->position.y < -1.05) rect->position.y += 2.1;
    }
}

void MyScene::MousePressed(Vec2 mouseLocation) {
    for (auto &rect : m_rects) {
        if (rect->Contains(mouseLocation)) {
            rect->color.z = 1.0;
        }else {
            rect->color.z = 0.0;
        }
    }
}

void MyScene::MouseReleased(Vec2 mouseLocation) {
    for (auto &rect : m_rects) {
        if (rect->Contains(mouseLocation)) {
            rect->color.z = 0.0;
        }
    }
}