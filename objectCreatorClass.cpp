#include "objectCreatorClass.h"
#include "sceneObjectClass.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

// Constructor for the grid creator
ObjectGridCreator::ObjectGridCreator(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	this->numObjects = rows * cols;
}

// Allocate the size needed for all scene objects to create
void ObjectGridCreator::Create(std::vector<SceneObject>& objects) {
	float rect_size = 1.0f / std::max(this->rows, this->cols);
	for (size_t row = 0; row < this->rows; row++) {
		float y = -1.0f + 2.0f / (this->rows + 1) * (row + 1);
		for (size_t col = 0; col < this->cols; col++) {
			float x = -1.0f + 2.0f / (this->cols + 1) * (col + 1);
			size_t index = this->GetGridIndex(row, col);
			SceneObject object;
			object.geometry = new SceneGeometryRect(x, y, rect_size, rect_size, 1.0f, 1.0f, 1.0f, 1.0f);

			
			// Now let's connect neighbours
			if (row) {
				int neighbourIndex = this->GetGridIndex(row - 1, col);
				objects[neighbourIndex].AddNeighbour(index);
				object.AddNeighbour(neighbourIndex);
			}else {
				// TODO: Add object equivalent to EdgePoint
			}

			if (col) {
				int neighbourIndex = this->GetGridIndex(row, col - 1);
				objects[neighbourIndex].AddNeighbour(index);
				object.AddNeighbour(neighbourIndex);
			}
			else {

			}
			

			objects.push_back(object);
		}
	}
}

int ObjectGridCreator::GetGridIndex(int row, int col) {
	return row * this->cols + col;
}
