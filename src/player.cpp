#include "player.hpp"


#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <p6/p6.h>

Player::Player():m_PosPlayer(0.,-1.8,-2.2){}; 

Player::Player(glm::vec3 posPlayer):m_PosPlayer(posPlayer){};

void Player::setPosition(glm::vec3 posPlayer)
{
    m_PosPlayer = posPlayer;
}

glm::vec3 Player::getPosition()
{
    return m_PosPlayer;
}

void Player::move(glm::vec3 distance){
    m_PosPlayer+=distance;
}

void Player::jumpPlayer(Player& player, float jumpHeight, float gravity, float deltaTime) {
    static float yVelocity = 0.f; // initial vertical velocity is 0

    // calculate new y velocity using v = v0 + at
    yVelocity += gravity * deltaTime;

    // calculate new player position
    glm::vec3 newPosition = player.getPosition() + glm::vec3(0.f, yVelocity, 0.f) * deltaTime;

    // if the player reaches the ground (y = 0), reset the y velocity and position
    if (newPosition.y <= 0.f) {
        newPosition.y = 0.f;
        yVelocity = jumpHeight;
    }

    // update player position
    player.setPosition(newPosition);


}

void Player::drawPlayer (glm::mat4 ViewMatrix , std::vector<glimac::ShapeVertex> vertices, glm::mat4 ProjMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix ){
    
    // glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, m_PosPlayer);
    // ViewMatrix = glm::rotate(ViewMatrix, 45.f, glm::vec3(1.,0.,0.));
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, -0.6, 0.0));
    
    ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
