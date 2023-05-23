#include "../src/game/include/obstacle.hpp"

Obstacle::Obstacle(const glm::vec3& position, float size)
    : position(position), size(size)
{
}

void Obstacle::avoid(glm::vec3& playerPosition) const
{
    // Calculer les limites de l'obstacle
    float minX = position.x - size / 2.0f;
    float maxX = position.x + size / 2.0f;
    float minZ = position.z - size / 2.0f;
    float maxZ = position.z + size / 2.0f;

    // Vérifier la position du joueur par rapport aux limites de l'obstacle
    if (playerPosition.x < minX)
        playerPosition.x = minX;
    else if (playerPosition.x > maxX)
        playerPosition.x = maxX;

    if (playerPosition.z < minZ)
        playerPosition.z = minZ;
    else if (playerPosition.z > maxZ)
        playerPosition.z = maxZ;
}