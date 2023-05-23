#version 330

//variables d'entrées
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

vec2 fCorrectCoords;

// out vec3 fFragColor;
out vec4 fFragColor;

uniform sampler2D uText;
// uniform sampler2D uTextIle;
// uniform sampler2D uTextPerso;
// uniform sampler2D uTextOiseau;

void main() {
	// vec4 textColor = texture(uTextIle, vTexCoords);
	// fFragColor = textColor.xyz;

	// fCorrectCoords = vec2(vTexCoords.x, 1-vTexCoords.y); //pour le template p6
	// vec4 normaleNormalise = vec4(normalize(vNormal_vs), 1.);

	fFragColor = texture(uText, vTexCoords) ;
	


	// fFragColor = texture(uTextIle, vTexCoords)+texture(uTextPerso)+texture(uTextOiseau, vTexCoords);
	// // fFragColor = textColor.xyz;
}