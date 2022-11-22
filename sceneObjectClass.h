#ifndef SCENE_OBJECT_CLASS_H
#define SCENE_OBJECT_CLASS_H

#include <glad/glad.h>

class SceneGeometry {
public:
	float vertices[];
	float indices[];
	SceneGeometry();

};

class SceneObject {
public:

	float x, y;
	SceneGeometry geo;

	SceneObject(float x, float y, SceneGeometry geo);
	void UpdatePos();
};


#endif