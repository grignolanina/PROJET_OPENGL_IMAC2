#version 330

layout(location = 3) in vec2 aVertexPosition;
layout(location = 8) in vec2 aVertexTexture;

out vec2 vFragPosition;

out vec2 vTexture;

uniform mat3 uModelMatrix;


void main() {

    vFragPosition=aVertexTexture;
    vTexture = (uModelMatrix*vec3(aVertexPosition,1)).xy;
    gl_Position = vec4(vTexture, 0,1);
}
