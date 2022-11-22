#include "sceneObjectClass.h"

/*
// SceneObject constructor
SceneObject::SceneObject(SceneGeometry *geometry) {
	this->geometry = geometry;
}*/

// Adds another SceneObject to the list of neighbours
void SceneObject::AddNeighbour(SceneObject* neighbour) {
	this->neighbours.push_back(neighbour);
}

// Updates the position of the scene object by moving it
// towards the average position of its neighbours
void SceneObject::UpdateGeometry() {
	float xAvg = 0;
	float yAvg = 0;
	for (auto& neighbour : this->neighbours) {
		xAvg += (neighbour->geometry->x - this->geometry->x);
		yAvg += (neighbour->geometry->y - this->geometry->y);
	}
	// alpha multiplies the distance to move.
	// Could be seen as an acceleration coefficient
	float alpha = 1.0f; 
	this->geometry->TranslatePosition(xAvg * alpha, yAvg * alpha);
}
