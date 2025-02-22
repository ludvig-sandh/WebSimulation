#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <memory>

#include "Vec2.h"
#include "Vec3.h"

class SceneObject {
public:
    Vec2 position;
    Vec3 color;
    float zIndex = 0;
    int32_t id = -1; // The object only receives a valid id after it has been added to a scene
    SceneObject(Vec2 position);
	void SetColor(float red, float green, float blue);
    void SetRotation(float angle);
    void SetScale(const Vec2 scale);
    void SetScale(const float scale);
    std::vector<float> GetVertices() const;
    virtual std::vector<int> GetIndices() const = 0;
	virtual bool Contains(const Vec2 &point) const = 0;
protected:
    std::vector<Vec2> m_points;
    float m_angle = 0.0f;
    Vec2 m_scale = Vec2(1.0f, 1.0f);
};

class SceneRect : public SceneObject {
public:
    Vec2 m_size;
    SceneRect(const Vec2 position, const Vec2 size, float red, float green, float blue);
    bool Contains(const Vec2 &point) const override;
    std::vector<int> GetIndices() const override;
};

// Convex polygon provided by a list of points in counterclockwise order.
class SceneConvexPolygon : public SceneObject {
public:
    SceneConvexPolygon(const Vec2 position, const std::vector<Vec2> points, float red, float green, float blue);
    std::vector<int> GetIndices() const override;
    bool Contains(const Vec2 &point) const override;
    void SetRotation(float angle);
    void SetScale(float scale);
private:
    std::vector<Vec2> m_topVertices, m_bottomVertices;
};

class SceneCircle : public SceneObject {
public:
    SceneCircle(const Vec2 position, float radius, float red, float green, float blue);
    SceneCircle(const Vec2 position, float radius, float red, float green, float blue, int resolution);
    std::vector<int> GetIndices() const override;
    bool Contains(const Vec2 &point) const override;
private:
    float m_radius;
    void InitCircle(float radius, int resolution);
};

// Used to order objects by id
struct SceneObjectIdComparator {
    bool operator()(const std::shared_ptr<SceneObject> &lhs,
                    const std::shared_ptr<SceneObject> &rhs) const {
        return lhs->id < rhs->id;
    }
};