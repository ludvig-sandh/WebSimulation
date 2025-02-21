#include <iostream>
#include <chrono>
#include <thread>

#include "glad/glad.h"
#include "WindowHandler.h"
#include "WindowException.h"
#include "FPSTracker.h"
#include "Config.h"
#include "MyScene.h"

// Since m_window (unique_ptr) needs a custom destroyer function, we have to specify it in the initializer list
WindowHandler::WindowHandler(const int screenWidth, const int screenHeight) : m_window(nullptr, glfwDestroyWindow) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    InitWindow();
    CreateScene();
}

WindowHandler::~WindowHandler() {
	// Terminate GLFW before ending the program
	glfwTerminate();
}

// Reads shaders from two shader files and binds graphics buffers
void WindowHandler::LoadShaders(const std::filesystem::path &vertexShaderPath, const std::filesystem::path &fragmentShaderPath) {
    try {
        m_shader = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath);
    }catch (const std::ios_base::failure& error) {
        if (m_window)
            // Delete window
            glfwDestroyWindow(m_window.get());

        // Terminate GLFW before ending the program
        glfwTerminate();

        throw error;
    }
    
    // Now that the shader is initialized, do some additional setup with the graphics library
    BindBuffers();
}

// Main while loop
void WindowHandler::RunMainLoop() {
    float minFrameTime = 1.0 / MAX_FPS;
    FPSTracker fpsTracker;
    while (!glfwWindowShouldClose(m_window.get())) {
        float timeFromLastFrame = fpsTracker.GetTimeFromLastFrame();
        if (timeFromLastFrame < minFrameTime) {
            // A bit of a dumb way to accurately sleep with <1ms precision
            static constexpr std::chrono::duration<double> minSleepDuration(0);
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < minFrameTime - timeFromLastFrame) {
                std::this_thread::sleep_for(minSleepDuration);
            }
        }

        // Keep track of frame times
        timeFromLastFrame = fpsTracker.RegisterNewFrame();

		// Here we update the scene
		m_scene->Update(timeFromLastFrame);
		m_scene->ComputeTriangles();
        
		// Link object to vertices
		m_vbo->Link(m_scene->getVertexBuffer(), m_scene->getVertexBufferCount() * sizeof(GLfloat));

        // Link object to indices
        m_ebo->Link(m_scene->getIndexBuffer(), m_scene->getIndexBufferCount() * sizeof(GLuint));
        
		// Redraw background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
        
		m_shader->Activate();
        
		// Handle interactions with the program
        HandleInteractions();
        
		glUniform1f(m_uniID, 0.0f);
		m_vao->Bind();

        // Draw all triangles
		glDrawElements(GL_TRIANGLES, m_scene->getIndexBufferCount(), GL_UNSIGNED_INT, 0);
        
		// Make sure to swap image buffers to display the correct frame
		glfwSwapBuffers(m_window.get());
        
		// Take care of all GLFW events
		glfwPollEvents();
	}
}

// Helper function to initialize GLFW and load necessary things related to GUI
void WindowHandler::InitWindow() {
    // Initialize GLFW
	glfwInit();

	// TELL GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window object width x height px, naming it "WebSimulation"
	GLFWwindow *window = glfwCreateWindow(m_screenWidth, m_screenHeight, "WebSimulation", NULL, NULL);

    // Assign the raw pointer to the smart pointer safely
    m_window.reset(window);

	// Error check if the window fails to create
	if (!m_window) {
        glfwTerminate();
        throw WindowException("Failed to initialize window.");
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(m_window.get());

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x = 0, y = 0, to x = 1000, y = 1000
	glViewport(0, 0, m_screenWidth, m_screenHeight);
}

void WindowHandler::BindBuffers() {
	// Generates Vertex Array Object and binds it
    m_vao = std::make_unique<VAO>();
    m_vao->Bind();
    
	// Generates Vertex Buffer Object
    m_vbo = std::make_unique<VBO>();

	// Generates Element Buffer Object and links it to indices
	m_ebo = std::make_unique<EBO>();
    m_ebo->Bind();

	// Links VBO to 
	m_vao->LinkAttrib(*m_vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	m_vao->LinkAttrib(*m_vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidental modifying
	m_vao->Unbind();
	m_vbo->Unbind();
	m_ebo->Unbind();

	m_uniID = glGetUniformLocation(m_shader->ID, "scale");
}

void WindowHandler::CreateScene() {
    m_scene = std::make_unique<MyScene>();
}

void WindowHandler::HandleInteractions() {
    Vec2 mouse_point;
	if (glfwGetMouseButton(m_window.get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		NormalizeCursorCoordinates(mouse_point);
		m_scene->MousePressed(mouse_point);
	}else if (glfwGetMouseButton(m_window.get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		NormalizeCursorCoordinates(mouse_point);
		m_scene->MouseReleased(mouse_point);
	}
}

// Finds the mouse coordinates and maps them into the range [-1, 1]
void WindowHandler::NormalizeCursorCoordinates(Vec2 &mouse_point) {
    double x, y;
	glfwGetCursorPos(m_window.get(), &x, &y);
	mouse_point.x = (float)x / m_screenWidth * 2.0 - 1.0;
	mouse_point.y = (float)y / m_screenHeight * -2.0 + 1.0;
}