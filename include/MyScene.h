#pragma once

#include "Scene.h"

class MyScene : public Scene {
public:
    MyScene(const Vec2 screenSize);
    void Update(float timeDelta) override;
	void MouseUpdate(Vec2 mouseLocation, bool isButtonDown) override;
private:
    std::vector<std::shared_ptr<SceneObject>> m_rects;
};