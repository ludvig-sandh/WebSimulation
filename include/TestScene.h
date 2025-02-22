#include "Scene.h"

class TestScene : public Scene {
public:
    TestScene();
	void Update(float timeDelta);
	void MousePressed(Vec2 mouseLocation);
	void MouseReleased(Vec2 mouseLocation);
private:
    std::shared_ptr<SceneObject> m_c1, m_c2, m_polyReal, m_polyTranslated, m_circle;
    float m_totalTime;
};