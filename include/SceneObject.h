#ifndef SCENE_OBJECT_CLASS_H
#define SCENE_OBJECT_CLASS_H

#include <vector>
#include "SceneGeometry.h"

class SceneObject {
public:
	SceneGeometry* geometry;
	std::vector<size_t> neighbours;
	std::vector<Vec2> staticNeighbours;
	bool isStatic = false;
	SceneObject() { this->geometry = NULL; }
	void AddNeighbour(size_t neighbourIndex);
	void AddStaticNeighbour(Vec2 neighbor);
	void UpdateGeometry(std::vector<SceneObject>& objects);
};

#endif