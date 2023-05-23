#pragma once

#include <glm/glm.hpp>
#include "../src/game/include/player.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"


class Obstacle {
private:
    glm::vec3 position;
    float     size;

public:
    ///\brief param constructor of the obstacle
    ///\param position the position of the obstacle
    ///\param size the size of the obstacle
    Obstacle(const glm::vec3& position, float size);

    ///\brief destructor of the obstacle
    ~Obstacle() = default;

    ///\brief verifier que le joueur ne rentre pas dans le position de l'obstacle
    ///\param playerPosition
    void avoid(glm::vec3& playerPosition) const;
};