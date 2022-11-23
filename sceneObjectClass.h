#ifndef SCENE_OBJECT_CLASS_H
#define SCENE_OBJECT_CLASS_H

#include <vector>
#include "sceneGeometryClass.h"

class SceneObject {
public:

	SceneGeometry* geometry;
	std::vector<int> neighbours;
	SceneObject() { this->geometry = NULL; }
	void AddNeighbour(int neighbourIndex);
	void UpdateGeometry(std::vector<SceneObject>& objects);
};

#endif