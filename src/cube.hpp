#pragma once

#include <glm/glm.hpp>
#include "glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include "p6/p6.h"
#include "program.hpp"
#include "player.hpp"

class Cube{
    private:
        std::vector<float> vertices;
        std::vector<GLuint> indices;
        GLuint vao, vbo, ibo;
        float m_size;
        GLuint texture;

class Cube {
private:
    std::vector<float>  vertices;
    std::vector<GLuint> indices;
    GLuint              vao, vbo, ibo;
    float               m_size;

        Cube(float size,  Program &program, img::Image &img_load);
        void clampPlayerPosition(Player &player);
        void draw(glm::vec3 pos, glm::vec3 scale,Program& program,glm::mat4 viewMatrix, glm::mat4 ProjMatrix) const;
        
};

void display();
