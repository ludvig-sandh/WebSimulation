#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
public:
    GLuint ID;
    VBO();
    ~VBO();
    
    // Delete copy constructor & assignment operator
    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;

    void Link(GLfloat* vertices, GLsizeiptr size);
    void Bind();
    void Unbind();
};


#endif