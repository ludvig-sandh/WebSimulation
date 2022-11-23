#include "sceneObjectClass.h"

/*
// SceneObject constructor
SceneObject::SceneObject(SceneGeometry *geometry) {
	this->geometry = geometry;
}*/

// Adds another SceneObject to the list of neighbours
void SceneObject::AddNeighbour(int neighbourIndex) {
	this->neighbours.push_back(neighbourIndex);
}

// Updates the position of the scene object by moving it
// towards the average position of its neighbours
void SceneObject::UpdateGeometry(std::vector<SceneObject>& objects) {
	// TODO: make sure edge objects cannot move
	// Add attribute isFixed for each object geometry.
	// All edges will be fixed, as well as the current object we 
	// are dragging
	float xAvg = 0;
	float yAvg = 0;
	for (auto& neighbourIdx : this->neighbours) {
		xAvg += (objects[neighbourIdx].geometry->x - this->geometry->x);
		yAvg += (objects[neighbourIdx].geometry->y - this->geometry->y);
	}
	// alpha multiplies the distance to move.
	// Could be seen as an acceleration coefficient
	float alpha = 1.0f;
	alpha = 0.3;
	this->geometry->TranslatePosition(xAvg * alpha, yAvg * alpha);
}
