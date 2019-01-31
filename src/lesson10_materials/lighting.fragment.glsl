#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

void main() {
    // Ambient light
    vec3 ambient = light.ambient * material.ambient;

    // Light direction
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);

    // Difuse light
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // Calculate view direction
    vec3 viewDir = normalize(viewPos - fragPos);

    // Calculate reflection direction
    vec3 reflectDir = reflect(-lightDir, norm);

    // Specular light
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    // Combine light and color contributions
    vec3 result = specular + diffuse + ambient;
    fragColor = vec4(result, 1.0);
}