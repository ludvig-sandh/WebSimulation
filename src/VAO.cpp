#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(layout);

	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}