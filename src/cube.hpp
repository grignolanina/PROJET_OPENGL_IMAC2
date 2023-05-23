#pragma once

#include <glm/glm.hpp>
#include "glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include "p6/p6.h"
#include "player.hpp"
#include "program.hpp"

class Cube {
private:
    std::vector<float>  vertices;
    std::vector<GLuint> indices;
    GLuint              vao, vbo, ibo;
    float               m_size;
    GLuint              texture;

public:
    explicit Cube(float size);
    void textures(img::Image& img_load);

    void vectors();
    void vertex();
    void borders(Player& player);
    void init(img::Image& img_load);
    void draw(glm::vec3 pos, glm::vec3 scale, Program& program, glm::mat4 viewMatrix, glm::mat4 ProjMatrix) const;
};

void display();
