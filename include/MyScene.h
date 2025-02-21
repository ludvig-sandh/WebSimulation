#pragma once

#include "Scene.h"

class MyScene : public Scene {
public:
    MyScene();
    void Update(float timeDelta) override;
	void MousePressed(Vec2 mouseLocation) override;
	void MouseReleased(Vec2 mouseLocation) override;
private:
    std::vector<std::shared_ptr<SceneObject>> m_rects;
};