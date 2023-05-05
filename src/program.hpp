#pragma once

#include <filesystem>
#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "glimac/sphere_vertices.hpp"
#include "glm/gtc/type_ptr.hpp"
#include<map>

class Program{
	private:
	std::filesystem::path m_vsPath;
	std::filesystem::path m_fsPath;
	p6::Shader m_program;
	std::map<std::string, GLint> m_uniformVariables;

	public:
	Program();
	Program(std::filesystem::path vsPath, std::filesystem::path fsPath):m_vsPath(vsPath), m_fsPath(fsPath), m_program(p6::load_shader(vsPath, fsPath)){};
	// ~Program();

	void addUniformVariable(const std::string &name);
	GLuint getId();
	void use();


	void uniformMatrix4fv(std::string name, glm::mat4 value);
	void uniform3fv(std::string name, glm::vec3 value);
	void uniform1i(std::string name, int value); //pour texture plus tard
	void uniform1f(std::string name, float value);

};


