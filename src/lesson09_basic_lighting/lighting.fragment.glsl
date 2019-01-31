#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
    // Ambient light
    float ambientStrength = .1;
    vec3 ambient = ambientStrength * lightColor;

    // Light direction
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // Difuse light
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine light and color contributions
    vec3 result = (ambient + diffuse) * objectColor;
    fragColor = vec4(result, 1.0);
}