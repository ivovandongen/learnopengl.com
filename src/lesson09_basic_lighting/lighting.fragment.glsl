#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    // Ambient light
    const float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Light direction
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // Difuse light
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Calculate view direction
    vec3 viewDir = normalize(viewPos - fragPos);

    // Calculate reflection direction
    vec3 reflectDir = reflect(-lightDir, norm);

    // Specular light
    const float specularStrength = 0.5;
    const int shinyness = 32;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinyness);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine light and color contributions
    vec3 result = (specular + diffuse + ambient) * objectColor;
    fragColor = vec4(result, 1.0);
}