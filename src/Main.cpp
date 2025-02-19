#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowHandler.h"

const int screenWidth = 2000;
const int screenHeight = 1000;

const std::filesystem::path vertexShaderPath = "../src/shaders/default.vert";
const std::filesystem::path fragmentShaderPath = "../src/shaders/default.frag";

int main() {
    WindowHandler windowHandler(screenWidth, screenHeight);
    windowHandler.LoadShaders(vertexShaderPath, fragmentShaderPath);
    windowHandler.RunMainLoop();
    return 0;
}