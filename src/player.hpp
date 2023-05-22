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

class Player{

	// private:
	// glm::vec3 m_PosPlayer; //camera position
	
    // public:
    // 	explicit Player(glm::vec3 posPlayer);
    //     Player();

    //     void move(glm::vec3 distance);

    //     void setPosition(glm::vec3 posPlayer);
    //     glm::vec3 getPosition ();
    //     // void drawPlayer(Model &model, glm::mat4 ViewMatrix, glm::mat4 ProjMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix,GLint uLightPos_vs, GLint uLightIntensity, GLint uKs, GLint uKd, GLint uShininess);
    //     void drawPlayer(Model &model, glm::mat4 ViewMatrix, glm::mat4 ProjMatrix, Program &program);

    private:
	glm::vec3 m_Position; //camera position
	float m_Phi; //coord spherique de F
	float m_Theta; //coord spherique de F
	float m_RotationAngle;

	glm::vec3 m_FrontVector; //vecteur F
	glm::vec3 m_LeftVector; //vecteur L
	glm::vec3 m_UpVector; //vecteur U


	void computeDirectionVectors();

	public:
	Player();
	Player(glm::vec3 position, float phi, float theta);

    void setPosition(glm::vec3 posPlayer);
    glm::vec3 getPosition();

	void setRotationAngle(float rotationAngle);
	float getRotationAngle() const;

	void moveLeft(float t); //deplacer la cam le long du vecteur L
	void moveFront(float t); //deplacer la cam le long di vecteur F

	void rotateLeft(float degrees); //modifie la rotation de la cam axe horizontal
	void rotateUp(float degrees); //modifie la rotation de la cam axe vertical

    


	glm::mat4 getViewMatrix() const;
    void drawPlayer(Model &model, glm::mat4 ViewMatrix, glm::mat4 ProjMatrix, Program &program);



};

void cameraOption(Player &camera,bool &left, bool &right, bool &up, bool &down,p6::Context& ctx);

        







