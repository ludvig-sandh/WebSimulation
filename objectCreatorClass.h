#ifndef OBJECT_CREATOR_CLASS_H
#define OBJECT_CREATOR_CLASS_H

#include "sceneObjectClass.h"

// Abstract base class for initializing the scene with new objects
class ObjectCreator {
public:
	int numObjects = 0;
	virtual void Create(std::vector<SceneObject> &objects) = 0;
};

// Class for creating a grid arrangement of new scene objects
class ObjectGridCreator : public ObjectCreator {
public:
	int rows, cols;
	ObjectGridCreator(int rows, int cols);
	void Create(std::vector<SceneObject>& objects);
};

#endif