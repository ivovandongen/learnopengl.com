#version 330 core

out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture1;

void main() {
    fragColor = texture(texture1, texCoords);
    float average = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
    fragColor = vec4(average, average, average, 1.0);
}