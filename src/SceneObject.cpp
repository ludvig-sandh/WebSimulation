#include "SceneObject.h"
#include "Vec2.h"

/*
// SceneObject constructor
SceneObject::SceneObject(SceneGeometry *geometry) {
	this->geometry = geometry;
}*/

// Adds another SceneObject to the list of neighbours
void SceneObject::AddNeighbour(size_t neighbourIndex) {
	this->neighbours.push_back(neighbourIndex);
}

void SceneObject::AddStaticNeighbour(Vec2 neighbor) {
	this->staticNeighbours.push_back(neighbor);
}

// Updates the position of the scene object by moving it
// towards the average position of its neighbours
void SceneObject::UpdateGeometry(std::vector<SceneObject>& objects) {
	// All edges will be fixed, as well as the current object we 
	// are dragging
	float xAvg = 0;
	float yAvg = 0;
	for (auto &neighbourIdx : this->neighbours) {
		xAvg += (objects[neighbourIdx].geometry->m_position.x - this->geometry->m_position.x);
		yAvg += (objects[neighbourIdx].geometry->m_position.y - this->geometry->m_position.y);
	}
	for (Vec2 &point : this->staticNeighbours) {
		xAvg += point.x - this->geometry->m_position.x;
		yAvg += point.y - this->geometry->m_position.y;
	}

	// alpha multiplies the distance to move.
	// Can be seen as an acceleration coefficient
	float alpha = 0.495;
	// alpha = 0.5f; // Also really cool but starts to get out of hand

    Vec2 translation;
    translation.x = xAvg * alpha;
    translation.y = yAvg * alpha;
	this->geometry->TranslatePosition(translation);
}
