#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Variables for window size so we can easily modify it
int width = 1000;
int height = 1000;

// Create vertices for our triangle
GLfloat vertices[] = {
//   X		 Y								Z	  COLORS
	-0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f, 0.9f, 0.45f, 0.17f, // Inner left
	 0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f, 0.9f, 0.45f, 0.17f, // Inner right
	 0.0f,  -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f,  0.02f  // Inner down
};

// Create the triangles with our vertices
GLuint indices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1  // Upper triangle
};

void handle_interactions(GLFWwindow *window) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY); 
	}else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
	}
}

int initWindow(GLFWwindow *window) {
	// Initialize GLFW
	glfwInit();

	// TELL GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object 1000x1000px naming it "WebSimulation"
	GLFWwindow* window = glfwCreateWindow(width, height, "WebSimulation", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x = 0, y = 0, to x = 1000, y = 1000
	glViewport(0, 0, width, height);
	
	return 0;
}

int main() {

	GLFWwindow* window;
	int resultCode = initWindow(window);
	if (resultCode) return resultCode;

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object
	VBO VBO1;

	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to 
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidental modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		for (int i = 0; i < sizeof(vertices) / (6 * sizeof(float)); i++) {
			vertices[i * 6] += 0.001;
		}

		// Link object to vertices
		VBO1.Link(vertices, sizeof(vertices));

		// Redraw background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		// Handle interactions with the program
		handle_interactions(window);

		glUniform1f(uniID, 1.0f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Make sure to swap image buffers to display the correct frame
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all objects we created so far
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}