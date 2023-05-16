#version 330

//variables d'entrées
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

vec2 fCorrectCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;


uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;//Ces 3 variables servent à représenter le matériau de l'objet en cours de dessin
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;//Ces deux variables servent à passer les informations sur la lumière au Shader 
uniform vec3 uLightPos2_vs;
uniform vec3 uLightIntensity2;//Ces deux variables servent à passer les informations sur la lumière au Shader 

vec3 blinnPhong(vec3 uLightPos_vs, vec3 uLightIntensity){
    float d = distance(vPosition_vs, uLightPos_vs);
    vec3 wi= normalize(uLightPos_vs-vPosition_vs);
    vec3 Li= (uLightIntensity/(d*d));
    vec3 w0 = (normalize(-vPosition_vs));
    vec3 N = vNormal_vs;
    vec3 halfVector = (w0+wi)/2.f;
    return Li*(uKd*(dot(wi, N))+uKs*pow(dot(halfVector,N),uShininess));
}


void main() {    
    // vec3 color = vec3(0.0, 0.0, 0.0);

    vec4 textColor = texture(uTexture, vTexCoords);

    
    // Calcul de la première lumière
    vec3 light1 = blinnPhong(uLightPos_vs, uLightIntensity);
    // color += vec4(light1,1);
    
    // Calcul de la deuxième lumière
    vec3 light2 = blinnPhong(uLightPos2_vs, uLightIntensity2);
    // color += vec4(light2,1);
    
    // fFragColor = color;

    // fFragColor = vec4(color, 1.0);
    // fFragColor = (light1+light2)*textColor.rgb;
    fFragColor = vec3(1., 0., 0.);

	
}