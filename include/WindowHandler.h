#pragma once

#include <memory>
#include <filesystem>

#include "GLFW/glfw3.h"
#include "Scene.h"
#include "Vec2.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class WindowHandler {
private:
    int m_screenWidth, m_screenHeight;
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;
    std::unique_ptr<Scene> m_scene;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<VAO> m_vao;
    std::unique_ptr<VBO> m_vbo;
    std::unique_ptr<EBO> m_ebo;
    GLuint m_uniID;
public:
    WindowHandler(const int screenWidth, const int screenHeight);
    ~WindowHandler();
    void LoadShaders(const std::filesystem::path &pathToVertexShader, const std::filesystem::path &pathToFragmentShader);
    void RunMainLoop();
private:
    void InitWindow();
    void BindBuffers();
    void CreateScene();
    void HandleInteractions();
    void NormalizeCursorCoordinates(Vec2 &mouseX);
};