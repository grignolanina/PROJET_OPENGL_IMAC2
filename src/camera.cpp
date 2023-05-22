#include "camera.hpp"
#include <p6/p6.h>
#include <cmath>
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "player.hpp"



Camera::Camera(Player& player, Model& model)
    : m_player(player), m_model(model), distance(0.5f), height(0.2f) {}

void Camera::update(glm::mat4& ViewMatrix)
{
    glm::mat4 modelRotationMatrix = glm::rotate(glm::mat4(1.0f), m_player.getRotationAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
    // Calcul de la position de la caméra en fonction de la viewMatrix du joueur
    glm::mat4 invPlayerViewMatrix = glm::inverse(ViewMatrix);
    auto playerPos= glm::vec3(invPlayerViewMatrix[3]); // La position du joueur correspond à la dernière colonne de la viewMatrix
    // glm::vec3 cameraPos = playerPos + distance * glm::vec3(invPlayerViewMatrix[2]) + height * glm::vec3(invPlayerViewMatrix[1]);

    glm::vec3 cameraPos = playerPos + distance * glm::vec3(modelRotationMatrix * glm::vec4(invPlayerViewMatrix[2])) + height * glm::vec3(invPlayerViewMatrix[1]);
    // Mise à jour de la vue de la caméra
    ViewMatrix = glm::lookAt(cameraPos, playerPos, glm::vec3(0.0f, 1.0f, 0.0f));
    m_model.setRotation(m_player.getRotationAngle()); 
}

