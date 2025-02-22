#include "TestScene.h"
#include <cmath>

TestScene::TestScene() : m_totalTime(0.0f) {
    m_c1 = std::make_shared<SceneRect>(Vec2(-0.25, 0), Vec2(0.3, 0.3), 1.0, 0.0, 0.0);
    m_c2 = std::make_shared<SceneRect>(Vec2(0.25, 0), Vec2(0.3, 0.3), 0.0, 0.0, 1.0);
    std::vector<Vec2> points = {Vec2(0.3, 0.2), Vec2(0.1, 0.4), Vec2(-0.2, 0.2), Vec2(-0.3, 0.0), Vec2(-0.15, -0.1), Vec2(0.1, -0.12), Vec2(0.2, -0.1)};
    m_polyReal = std::make_shared<SceneConvexPolygon>(Vec2(0.0, 0.0), points, 0.0, 0.6, 0.0);
    m_polyTranslated = std::make_shared<SceneConvexPolygon>(Vec2(0.0, 0.2), points, 0.0, 0.9, 0.0);
    m_circle = std::make_shared<SceneCircle>(Vec2(0.0, 0.0), 0.01, 1.0, 1.0, 1.0);

    AddObject(m_c1);
    AddObject(m_c2);
    AddObject(m_polyReal);
    AddObject(m_polyTranslated);
    AddObject(m_circle);
}

void TestScene::Update(float timeDelta) {
    m_totalTime += timeDelta;
    m_c1->SetRotation(m_totalTime);
    m_c2->SetRotation(-m_totalTime);
    m_polyTranslated->SetRotation(m_totalTime);
    m_c1->SetScale(sin(m_totalTime));
    m_c2->SetScale(Vec2(cos(m_totalTime + 3.14f), sin(-m_totalTime + 3.14f)));
    m_polyTranslated->SetScale(Vec2(cos(m_totalTime + 1.14f), sin(-m_totalTime - 1.14f)));
    m_c1->position.x = -0.25 + 0.2 * cos(-m_totalTime);
    m_c2->position.x = 0.25 + 0.2 * cos(m_totalTime);
    m_c1->position.y = 0.2 * sin(-m_totalTime);
    m_c2->position.y = 0.2 * sin(m_totalTime);
}

void TestScene::MousePressed(Vec2 mouseLocation) {
    m_c1->color.y = m_c1->Contains(mouseLocation) ? 1.0 : 0.0;
    m_c2->color.y = m_c2->Contains(mouseLocation) ? 1.0 : 0.0;
    m_polyReal->color.x = m_polyReal->Contains(mouseLocation) ? 1.0 : 0.0;
    m_polyTranslated->color.x = m_polyTranslated->Contains(mouseLocation) ? 1.0 : 0.0;

    // Set cursor translated
    m_circle->position = ((mouseLocation - Vec2(0.0, 0.2)) / Vec2(cos(m_totalTime + 1.14f), sin(-m_totalTime - 1.14f))).rotate(-m_totalTime);
}

void TestScene::MouseReleased(Vec2 mouseLocation) {

}