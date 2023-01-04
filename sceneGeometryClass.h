#ifndef SCENE_GEOMETRY_CLASS_H
#define SCENE_GEOMETRY_CLASS_H

#include <vector>

class SceneGeometry {
public:
	float x = 0, y = 0;
	float startX, startY;
	float lastX, lastY;
	size_t numVertices = 0;
	std::vector<float> vertices;
	void TranslatePosition(float dx, float dy);
	void SetColor(float red, float green, float blue);
	virtual bool Contains(float xOther, float yOther) = 0;
};

class SceneGeometryRect : public SceneGeometry {
public:
	float width, height;
	SceneGeometryRect(float x, float y, float width, float height, 
					  float red, float green, float blue);
	bool Contains(float xOther, float yOther);
};

#endif