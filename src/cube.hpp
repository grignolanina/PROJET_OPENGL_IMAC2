#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "glimac/sphere_vertices.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include "program.hpp"

class Cube{
    private:
        std::vector<float> vertices;
        std::vector<GLuint> indices;
        GLuint vao, vbo, ibo;
        float m_size;

    public :

        explicit Cube(float size);

        void draw() const;
        
};

void display();

