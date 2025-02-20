#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
	GLuint ID;
	EBO();
    ~EBO();

    void Link(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
};


#endif