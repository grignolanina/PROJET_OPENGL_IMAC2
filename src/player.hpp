#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "glimac/sphere_vertices.hpp"
#include "glm/gtc/type_ptr.hpp"



class Player{

	private:
	glm::vec3 m_PosPlayer; //camera position
	
    public:
    	explicit Player(glm::vec3 posPlayer);
        Player();

        void move(glm::vec3 distance);

        void setPosition(glm::vec3 posPlayer);
        glm::vec3 getPosition ();
        void drawPlayer (glm::mat4 ViewMatrix,  std::vector<glimac::ShapeVertex> vertices, glm::mat4 ProjMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix);
        void jumpPlayer(Player& player, float jumpHeight, float gravity, float deltaTime);


};




