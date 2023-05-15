#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "program.hpp"

class Light {
private:
    glm::vec3 m_pos;
    glm::vec3 m_intensity;

public:
    Light();
    Light(glm::vec3 pos, glm::vec3 intensity)
        : m_pos(pos), m_intensity(intensity){};

    glm::vec3 getPos()
    {
        return m_pos;
    }
    glm::vec3 getIntensity()
    {
        return m_intensity;
    }
};