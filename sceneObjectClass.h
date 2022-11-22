#ifndef SCENE_OBJECT_CLASS_H
#define SCENE_OBJECT_CLASS_H

#include <vector>
#include "sceneGeometryClass.h"

class SceneObject {
public:

	SceneGeometry* geometry;
	std::vector<SceneObject*> neighbours;
	SceneObject() { this->geometry = NULL; }; // Dummy constructor
	SceneObject(SceneGeometry *geometry);
	void AddNeighbour(SceneObject *neighbour);
	void UpdateGeometry();
};

#endif