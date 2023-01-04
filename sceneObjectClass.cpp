#include "sceneObjectClass.h"

/*
// SceneObject constructor
SceneObject::SceneObject(SceneGeometry *geometry) {
	this->geometry = geometry;
}*/

// Adds another SceneObject to the list of neighbours
void SceneObject::AddNeighbour(size_t neighbourIndex) {
	this->neighbours.push_back(neighbourIndex);
}

void SceneObject::AddStaticNeighbour(float x, float y) {
	this->staticNeighbours.push_back(std::make_pair(x, y));
}

// Updates the position of the scene object by moving it
// towards the average position of its neighbours
void SceneObject::UpdateGeometry(std::vector<SceneObject>& objects) {
	// All edges will be fixed, as well as the current object we 
	// are dragging
	float xAvg = 0;
	float yAvg = 0;
	for (auto& neighbourIdx : this->neighbours) {
		xAvg += (objects[neighbourIdx].geometry->x - this->geometry->x);
		yAvg += (objects[neighbourIdx].geometry->y - this->geometry->y);
	}
	for (auto& point : this->staticNeighbours) {
		xAvg += point.first - this->geometry->x;
		yAvg += point.second - this->geometry->y;
	}

	// alpha multiplies the distance to move.
	// Can be seen as an acceleration coefficient
	float alpha = 0.495;
	// alpha = 0.5f; // Also really cool but starts to get out of hand
	this->geometry->TranslatePosition(xAvg * alpha, yAvg * alpha);
}
