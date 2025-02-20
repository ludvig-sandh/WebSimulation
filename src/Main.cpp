#include <filesystem>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "WindowHandler.h"
#include "Config.h"

const std::filesystem::path vertexShaderPath = "../src/shaders/default.vert";
const std::filesystem::path fragmentShaderPath = "../src/shaders/default.frag";

int main() {
    WindowHandler windowHandler(SCREEN_WIDTH, SCREEN_HEIGHT);
    windowHandler.LoadShaders(vertexShaderPath, fragmentShaderPath);
    windowHandler.RunMainLoop();
    return 0;
}