#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "player.hpp"

class Obstacle {
private:
    glm::vec3 position;
    float     size;

public:
    Obstacle(const glm::vec3& position, float size);

    void avoid(glm::vec3& playerPosition) const;
};