#pragma once

#include <map>
#include "Scene.h"

class VoronoiScene : public Scene {
public:
    VoronoiScene(const Vec2 screenSize);
    
    void Update(float timeDelta);

    std::vector<std::shared_ptr<SceneObject>> polies;
    std::map<Vec2, Vec3> colors;
    void ComputeVoronoiDiagram();

    bool mouseDownLast = false;
    std::vector<Vec2> m_points;
	void MouseUpdate(Vec2 mouseLocation, bool isButtonDown);
};