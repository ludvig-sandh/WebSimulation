#include "VBO.h"
#include <iostream>

VBO::VBO() {
	glGenBuffers(1, &ID);
}

void VBO::Link(GLfloat* vertices, GLsizeiptr size) {
	glBindBuffer(GL_ARRAY_BUFFER, ID); // There are different buffer types
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}