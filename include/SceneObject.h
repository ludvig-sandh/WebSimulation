#pragma once

#include <vector>
#include "SceneGeometry.h"
#include "Vec2.h"
#include "Vec3.h"

class SceneObject {
public:
    Vec2 position;
    Vec3 color;
    float zIndex = 0;
	void SetColor(float red, float green, float blue);
	virtual bool Contains(const Vec2 &point) const = 0;
    virtual std::vector<float> GetVertices() const = 0;
    virtual std::vector<int> GetIndices() const = 0;
    SceneObject(Vec2 position);
};

class SceneRect : public SceneObject {
public:
    Vec2 m_size;
    SceneRect(const Vec2 position, const Vec2 size, float red, float green, float blue);
    std::vector<float> GetVertices() const override;
    std::vector<int> GetIndices() const override;
    bool Contains(const Vec2 &point) const override;
};

// Convex polygon provided by a list of points in counterclockwise order.
class SceneConvexPolygon : public SceneObject {
public:
    SceneConvexPolygon(const std::vector<Vec2> &points, float red, float green, float blue);
    std::vector<float> GetVertices() const override;
    std::vector<int> GetIndices() const override;
    bool Contains(const Vec2 &point) const override;
private:
    std::vector<Vec2> m_points;
    std::vector<Vec2> m_topVertices, m_bottomVertices;
};