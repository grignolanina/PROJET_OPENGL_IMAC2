#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "player.hpp"



class Camera {
	private:
	
	Player& m_player;
    GLfloat m_horizontal;
    GLfloat m_vertical;
	GLfloat m_distance;


	public:
	
	explicit Camera(Player& player); //constructeur par défaut
	Camera(Player& player, GLfloat horizontal, GLfloat vertical, GLfloat distance);//Constructeur



    void setDistance(GLfloat distance);//Distace séparant la caméra du joueur
    GLfloat getDistance()const;

    void setHorizontal(float angle);//Angle pour pivoter horizontalement
	GLfloat getHorizontal()const;

    void setVertical(float angle);//Angle pour pivoter verticalement
	GLfloat getVertical()const;

	void moveFront(GLfloat amount); //deplacement vers l'avant


	void rotateHorizontal(float angle); //modifie la rotation de la cam axe horizontal
	void rotateVertical(float angle); //modifie la rotation de la cam axe vertical

	void moveRight(float amount); //déplacement vers la droite
	

	glm::mat4 update(); //Update les positions de la cam pour pouvoir bouger en même temps que le personnage



};

void cameraOption(Camera &camera, bool &left, bool &right, bool &up, bool &down, p6::Context& ctx);
