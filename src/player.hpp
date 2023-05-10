#pragma once

#include <glm/glm.hpp>
#include "glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include "p6/p6.h"
#include "program.hpp"

class Player {
private:
    glm::vec3 m_PosPlayer; // camera position

public:
    explicit Player(glm::vec3 posPlayer);
    Player();

    void move(glm::vec3 distance);

    void      setPosition(glm::vec3 posPlayer);
    glm::vec3 getPosition();
    // void drawPlayer(Model &model, glm::mat4 ViewMatrix, glm::mat4 ProjMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix,GLint uLightPos_vs, GLint uLightIntensity, GLint uKs, GLint uKd, GLint uShininess);
    void drawPlayer(Model& model, glm::mat4 ViewMatrix, glm::mat4 ProjMatrix, Program& program);
};
