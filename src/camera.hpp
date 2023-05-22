#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "player.hpp"

class Camera {
private:
    // glm::mat4 viewmatrix;
    // glm::mat4 projmatrix;
    Player m_player;
    Model& m_model;
    float  distance;
    float  height;

public:
    explicit Camera(Player& player, Model& model); // constructeur par défaut
    void update(glm::mat4& viewMatrix);            // Update les positions de la cam pour pouvoir bouger en même temps que le personnage
};

// void cameraOption(Camera& camera, bool& left, bool& right, bool& up, bool& down, p6::Context& ctx);