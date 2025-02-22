#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "MyScene.h"

MyScene::MyScene(const Vec2 screenSize) : Scene(screenSize) {
    // Example code for some rectangles
    int rows = 200;
    int cols = 200;
    float w = screenSize.x / (float)cols;
    float h = screenSize.y / (float)rows;
    for (int c = 0; c < rows; c++) {
        for (int r = 0; r < cols; r++) {
            float x = -1.05 + 0.03 * c;
            float y = -1.05 + 0.03 * r;
            float red = fmod((x + y) * (x + y), 1.0f);
            float green = fmod((x - y) * (x + y), 1.0f);
            float blue = fmod((x - y) * (x - y), 1.0f);
            Vec2 pos = Vec2(w / 2 + w * c, h / 2 + h * r);
            std::shared_ptr<SceneRect> rect = std::make_shared<SceneRect>(pos, Vec2(w, h), pos.x / screenSize.x, pos.y / screenSize.y, 1.0);
            m_rects.push_back(rect);
            AddObject(rect);
        }
    }
}

void MyScene::Update(float timeDelta) {
    int rows = 200;
    int cols = 200;
    float w = m_screenSize.x / (float)cols;
    float h = m_screenSize.y / (float)rows;

    // // Example code for some rectangles
    for (auto &rect : m_rects) {
        float x = rect->position.x / m_screenSize.x * 2.0 - 1.0;
        float y = rect->position.y / m_screenSize.y * 2.0 - 1.0;
        float dx = (0.5 - x - y) * (-x + y);
        float dy = (x + y) * (-0.5 - x + y);
        
        rect->position += Vec2(dx, -dy) * 1000 * timeDelta;
        if (rect->position.x > m_screenSize.x + w / 2) rect->position.x = -w / 2;
        if (rect->position.x < -w / 2) rect->position.x = m_screenSize.x + w / 2;
        if (rect->position.y > m_screenSize.y + h / 2) rect->position.y = -h / 2;
        if (rect->position.y < -h / 2) rect->position.y = m_screenSize.y + h / 2;
    }
}

void MyScene::MouseUpdate(Vec2 mouseLocation, bool isButtonDown) {
    if (isButtonDown) {
        std::vector<std::shared_ptr<SceneObject>> newRects;
        for (auto &rect : m_rects) {
            if (rect->Contains(mouseLocation)) {
                RemoveObject(rect);
            }else {
                newRects.push_back(rect);
            }
        }
        m_rects = newRects;
    }
}