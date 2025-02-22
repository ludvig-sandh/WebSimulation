#include "Scene.h"

class TestScene : public Scene {
public:
    TestScene(const Vec2 screenSize);
	void Update(float timeDelta) override;
	void MouseUpdate(Vec2 mouseLocation, bool isButtonDown) override;
private:
    std::shared_ptr<SceneObject> m_c1, m_c2, m_polyReal, m_polyTranslated, m_circle;
    float m_totalTime;
};