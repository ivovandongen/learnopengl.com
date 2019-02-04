#version 330 core

out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture1;

void main() {
    fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}