#include "player.hpp"


#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <p6/p6.h>
#include <vector>


void Player::setPosition(glm::vec3 posPlayer)
{
    m_Position = posPlayer;
}

glm::vec3 Player::getPosition()
{
    return m_Position;
}

float Player::getRotationAngle() const {
    return m_RotationAngle; // Remplacez m_RotationAngle par la variable ou la valeur appropriée contenant l'angle de rotation de votre modèle
}

void Player::setRotationAngle(float rotationAngle) {
    m_RotationAngle = rotationAngle; // Remplacez m_RotationAngle par la variable ou la valeur appropriée contenant l'angle de rotation de votre modèle
}


Player::Player():m_Position(glm::vec3(0., 0., 0.)), m_Phi(p6::PI), m_Theta(0.),m_RotationAngle(0.){
	this->computeDirectionVectors();
};

Player::Player(glm::vec3 position, float phi, float theta):m_Position(position), m_Phi(phi), m_Theta(theta){
	this->computeDirectionVectors();
};

void Player::computeDirectionVectors(){
	m_FrontVector = glm::vec3(glm::cos(m_Theta)*glm::sin(m_Phi), glm::sin(m_Theta), glm::cos(m_Theta)*glm::cos(m_Phi));
	m_LeftVector = glm::vec3(glm::sin(m_Phi+(p6::PI/2)), 0, glm::cos(m_Phi+(p6::PI/2)));
	m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void Player::moveLeft(float t){
	m_Position += t*m_LeftVector;
	computeDirectionVectors();
}
void Player::moveFront(float t){
	m_Position += t*m_FrontVector;
	computeDirectionVectors();
}

void Player::rotateLeft(float degrees){
	m_Phi += glm::radians(degrees);
	computeDirectionVectors();
}
void Player::rotateUp(float degrees){
	m_Theta += glm::radians(degrees);
	computeDirectionVectors();
}

glm::mat4 Player::getViewMatrix() const{
	return glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
}



void cameraOption(Player &player, bool &left, bool &right, bool &up, bool &down,p6::Context& ctx)	{
        if(right){
            player.rotateLeft(-0.5f);
        }
        if(left){
            player.rotateLeft(+0.5f);
        }
        if(up){
            player.moveFront(0.05f);
        }
        if(down){
            player.moveFront(-0.05f);
        }

        ctx.key_pressed = [&right, &up, &left, &down](p6::Key key){
            if(key.logical == "d"){
                right = true;
            }
            if(key.logical == "q"){
                left = true;
            }
            if(key.logical == "z"){
                up = true;
            }
            if(key.logical == "s"){
                down = true;
            }
        };

        ctx.key_released = [&right, &up, &left, &down](p6::Key key){
            if(key.logical == "d"){
                right = false;
            }
            if(key.logical == "q"){
                left = false;
            }
            if(key.logical == "z"){
                up = false;
            }
            if(key.logical == "s"){
                down = false;
            }
        };

        ctx.mouse_dragged = [&player](const p6::MouseDrag& button) {
            player.rotateLeft(button.delta.x * 5);
            player.rotateUp(-button.delta.y * 5);
        };

        ctx.mouse_scrolled = [&](p6::MouseScroll scroll){

            player.moveFront(-scroll.dy);
        };

		
	
	
        

}


void Player::drawPlayer(Model &model, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, Program &program){
    
    viewMatrix = glm::translate(viewMatrix, m_Position);
    
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -0.7, 0.0));
    viewMatrix = glm::scale(viewMatrix, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(viewMatrix));

    

    program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * viewMatrix);
    program.uniformMatrix4fv("uMVMatrix", viewMatrix);
    program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);



    program.uniform3fv("uKd", (glm::vec3(0.2f, 0.1f, 0.15f)));
    program.uniform3fv("uKs", (glm::vec3(0.2f, 0.1f, 0.1f)));
    program.uniform1f("uShininess", 0.6);


    program.uniform3fv("uLightPos_vs", (glm::vec3(glm::translate(viewMatrix, glm::vec3(0, 5, 0)) * glm::vec4(1, 1, 0, 1))));
    program.uniform3fv("uLightIntensity", (glm::vec3(0.7, 0.7, 0.7)));



    model.drawArray();

    
}
