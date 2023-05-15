#version 330

in vec2 vTexture;
in vec2 vFragPosition;

out vec2 fFragTexture;
uniform vec3 uColor=vec3(1,1,1);
uniform sampler2D uTexture;

void main() {
    vec4 T = vec4(texture(uTexture,vFragPosition));
    fFragTexture = vec2(T.xy);

}