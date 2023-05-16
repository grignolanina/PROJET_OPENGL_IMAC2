#version 330

//variables d'entrées
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

vec2 fCorrectCoords;

// out vec3 fFragColor;
out vec3 fFragColor;

uniform sampler2D uTextDuck;
// uniform sampler2D uTextPerso;

void main() {
	vec4 textColor = texture(uTextDuck, vTexCoords);
	fFragColor = textColor.xyz;
}