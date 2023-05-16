#version 330

//variables d'entrées
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

vec2 fCorrectCoords;

out vec4 fFragColor;

// uniform sampler2D uTextTerre;
// uniform sampler2D uTextMoon;

// uniform sampler2D uTexture1;
// uniform sampler2D uTexture2;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;//Ces 3 variables servent à représenter le matériau de l'objet en cours de dessin
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;//Ces deux variables servent à passer les informations sur la lumière au Shader 

vec3 blinnPhong(){
    float d = distance(vPosition_vs, uLightPos_vs);
    vec3 wi= normalize(uLightPos_vs-vPosition_vs);
    vec3 Li= (uLightIntensity/(d*d));
    vec3 w0 = (normalize(-vPosition_vs));
    vec3 N = vNormal_vs;
    vec3 halfVector = (w0+wi)/2.f;
    return Li*(uKd*(dot(wi, N))+uKs*pow(dot(halfVector,N),uShininess));
}


void main() {

	

    // fCorrectCoords = vec2(vTexCoords.x, 1-vTexCoords.y); //pour le template p6
	// vec4 normaleNormalise = vec4(normalize(vNormal_vs), 1.);

	// fFragColor = texture(uTextTerre, fCorrectCoords) + texture(uTextMoon, fCorrectCoords);
	// fFragColor = vec4(1., 1., 0., 1.);
	// vec3 normal = normalize(vNormal_vs);
    // fFragColor = normal.xzy;

    

	fFragColor = vec4(blinnPhong(),1.);
	
    // fFragColor = texture(uTexture1, fCorrectCoords) + texture(uTexture2, fCorrectCoords);
}