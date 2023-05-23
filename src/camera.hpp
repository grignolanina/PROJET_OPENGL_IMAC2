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
    /// \brief default constuctor of the camera
    explicit Camera(Player& player, Model& model);

    ///\brief destructor of the camera
    ~Camera() = default;

    /// \brief update camera position to move the player in the same time
    /// \param viewMatrix the camera
    void update(glm::mat4& viewMatrix);
};