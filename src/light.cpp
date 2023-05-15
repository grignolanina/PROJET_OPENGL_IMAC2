// #include "light.hpp"
// #include "glm/fwd.hpp"

// void Light::drawLight(glm::mat4 viewMatrix, Program& program, glm::mat4 projMatrix, glm::mat4 normalMatrix, glm::vec3 pos)
// {
//     glm::mat4 ViewMatrixLight = viewMatrix;
//     program.use();
//     program.uniform3fv("uKd", glm::vec3(0.2f, 0.1f, 0.15f));
//     program.uniform3fv("uKs", glm::vec3(0.2f, 0.1f, 0.1f));
//     program.uniform1f("uShininess", 0.6);

//     glm::vec4 LightPos = viewMatrix * glm::vec4(pos, 1.0);
//     program.uniform3fv("uLightPos_vs", glm::vec3(LightPos.x, LightPos.y, LightPos.z));

//     program.uniform3fv("uLightIntensity", glm::vec3{600});

//     program.uniformMatrix4fv("uMVPMatrix", projMatrix * ViewMatrixLight);
//     program.uniformMatrix4fv("uMVMatrix", ViewMatrixLight);
//     program.uniformMatrix4fv("uNormalMatrix", normalMatrix);
// }