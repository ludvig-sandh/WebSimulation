#pragma once

#include <filesystem>
#include <string>
#include "glad/glad.h"

std::string get_file_contents(const std::filesystem::path &filename);

class Shader {
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that build the Shader Program from 2 different shaders
		Shader(const std::filesystem::path &vertexFile, const std::filesystem::path &fragmentFile);

		// Deletes the Shader Program
        ~Shader();

		// Activates the Shader Program
		void Activate();
	private:
		// Checks if the different Shaders have compiled properly
		void compileErrors(unsigned int shader, const char* type);
};