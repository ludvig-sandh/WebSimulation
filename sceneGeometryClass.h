#ifndef SCENE_GEOMETRY_CLASS_H
#define SCENE_GEOMETRY_CLASS_H

#include <vector>

class SceneGeometry {
public:
	float x = 0, y = 0;
	size_t numVertices = 0, numIndices = 0;
	std::vector<float> vertices;
	std::vector<int> indices;
	void TranslatePosition(float dx, float dy);
	virtual bool Contains(float xOther, float yOther) = 0;
};

class SceneGeometryRect : public SceneGeometry {
public:
	float width, height;
	SceneGeometryRect(float x, float y, float width, float height, 
					  float red, float green, float blue, float alpha);
	bool Contains(float xOther, float yOther);
};

#endif