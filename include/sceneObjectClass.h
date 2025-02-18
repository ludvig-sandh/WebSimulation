#ifndef SCENE_OBJECT_CLASS_H
#define SCENE_OBJECT_CLASS_H

#include <vector>
#include "sceneGeometryClass.h"

class SceneObject {
public:

	SceneGeometry* geometry;
	std::vector<size_t> neighbours;
	std::vector<std::pair<float, float>> staticNeighbours;
	bool isStatic = false;
	SceneObject() { this->geometry = NULL; }
	void AddNeighbour(size_t neighbourIndex);
	void AddStaticNeighbour(float x, float y);
	void UpdateGeometry(std::vector<SceneObject>& objects);
};

#endif