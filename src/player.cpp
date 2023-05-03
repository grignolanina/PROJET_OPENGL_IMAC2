#include "player.hpp"


#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <p6/p6.h>
#include <vector>

Player::Player():m_PosPlayer(0.,-2,-2.2){}; 

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



void Player::drawPlayer (glm::mat4 ViewMatrix,  std::vector<glimac::ShapeVertex> vertices, glm::mat4 ProjMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix,GLint uLightPos_vs, GLint uLightIntensity, GLint uKs, GLint uKd, GLint uShininess, p6::Context& ctx){
    
    // glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, m_PosPlayer);
    // ViewMatrix = glm::rotate(ViewMatrix, 45.f, glm::vec3(1.,0.,0.));
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, -0.7, 0.0));
    
    ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
    glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
    glUniform1f(uShininess, 0.6);

    // glUniform3fv(uLightPos_vs, 1, glm::value_ptr(glm::vec3(glm::rotate(ViewMatrix, ctx.time(), glm::vec3(0, 1, 0)) * glm::vec4(1, 1, 0, 1))));

    glUniform3fv(uLightPos_vs, 1, glm::value_ptr(glm::vec3(glm::translate(ViewMatrix, glm::vec3(0, 5, 0)) * glm::vec4(1, 1, 0, 1))));

    glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
    
    
    // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    
}
