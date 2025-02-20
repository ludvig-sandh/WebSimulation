#include "EBO.h"

EBO::EBO() {
	glGenBuffers(1, &ID);
}

EBO::~EBO() {
	glDeleteBuffers(1, &ID);
}

void EBO::Link(GLuint* indices, GLsizeiptr size) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // There are different buffer types
	// Introduce the vertices into the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}