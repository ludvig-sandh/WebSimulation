#pragma once

#include <vector>
#include "Vec2.h"

class SceneGeometry {
public:
    Vec2 m_position, m_startPosition, m_lastPosition;
	size_t numVertices = 0, numIndices = 0;
	std::vector<float> vertices;
	std::vector<int> indices;
	void TranslatePosition(const Vec2 &translation);
	void SetColor(float red, float green, float blue);
	virtual bool Contains(const Vec2 &point) = 0;
};

class SceneGeometryRect : public SceneGeometry {
public:
    Vec2 m_size;
	SceneGeometryRect(const Vec2 &position, const Vec2 &size,
        float red, float green, float blue);
	bool Contains(const Vec2 &point);
};