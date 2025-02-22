#include <cmath>
#include <iostream>
#include "TestScene.h"

TestScene::TestScene(const Vec2 screenSize) : Scene(screenSize), m_totalTime(0.0f) {
    Vec2 center = screenSize / 2.0;
    float tenthX = screenSize.x / 10.0;
    float tenthY = screenSize.y / 10.0;
    Vec2 dx = Vec2(tenthX, 0.0);
    Vec2 dy = Vec2(0.0, tenthY);
    m_c1 = std::make_shared<SceneRect>(center - dx + dy, Vec2(tenthX, tenthX), 1.0, 0.0, 0.0);
    m_c2 = std::make_shared<SceneRect>(center + dx - dy, Vec2(tenthX, tenthX), 0.0, 0.0, 1.0);
    std::vector<Vec2> points = {Vec2(0.3, 0.2), Vec2(0.1, 0.4), Vec2(-0.2, 0.2), Vec2(-0.3, 0.0), Vec2(-0.15, -0.1), Vec2(0.1, -0.12), Vec2(0.2, -0.1)};
    for (Vec2 &point : points) {
        point *= center;
        point.y *= -1.0;
    }
    m_polyReal = std::make_shared<SceneConvexPolygon>(center, points, 0.0, 0.6, 0.0);
    m_polyTranslated = std::make_shared<SceneConvexPolygon>(center - dy, points, 0.0, 0.9, 0.0);
    m_circle = std::make_shared<SceneCircle>(center, tenthY, 0.5, 0.5, 0.5);

    AddObject(m_c1);
    AddObject(m_c2);
    AddObject(m_polyReal);
    AddObject(m_polyTranslated);
    AddObject(m_circle);
}

void TestScene::Update(float timeDelta) {
    Vec2 center = m_screenSize / 2.0;
    float tenthX = m_screenSize.x / 10.0;
    float tenthY = m_screenSize.y / 10.0;
    Vec2 dx = Vec2(tenthX, 0.0);
    Vec2 dy = Vec2(0.0, tenthY);
    m_totalTime += timeDelta;
    m_c1->SetRotation(m_totalTime);
    m_c2->SetRotation(-m_totalTime);
    m_polyTranslated->SetRotation(m_totalTime);
    m_c1->SetScale(sin(m_totalTime));
    m_c2->SetScale(Vec2(cos(m_totalTime + 3.14f), sin(-m_totalTime + 3.14f)));
    m_polyTranslated->SetScale(Vec2(cos(m_totalTime + 1.14f), sin(-m_totalTime - 1.14f)));
    m_c1->position.x = center.x - dx.x + tenthX * cos(-m_totalTime);
    m_c2->position.x = center.x + dx.x + tenthX * cos(m_totalTime);
    m_c1->position.y = tenthX * sin(-m_totalTime);
    m_c2->position.y = tenthX * sin(m_totalTime);
}

void TestScene::MouseUpdate(Vec2 mouseLocation, bool isButtonDown) {
    if (isButtonDown) {
        m_c1->color.y = m_c1->Contains(mouseLocation) ? 1.0 : 0.0;
        m_c2->color.y = m_c2->Contains(mouseLocation) ? 1.0 : 0.0;
        m_polyReal->color.x = m_polyReal->Contains(mouseLocation) ? 1.0 : 0.0;
        m_polyTranslated->color.x = m_polyTranslated->Contains(mouseLocation) ? 1.0 : 0.0;
        m_circle->color.z = m_circle->Contains(mouseLocation) ? 1.0 : 0.5;
    }
}