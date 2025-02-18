#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
	GLuint ID;
	EBO(GLuint* incides, GLsizeiptr size);
    ~EBO();

	void Bind();
	void Unbind();
};


#endif