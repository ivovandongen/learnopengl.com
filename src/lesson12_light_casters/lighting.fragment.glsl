#version 330 core

out vec4 fragColor;

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

void main() {
    // Ambient light
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

    // Light direction
    vec3 lightDir = normalize(-light.direction);

    // Difuse light
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));

    // Calculate view direction
    vec3 viewDir = normalize(viewPos - fragPos);

    // Calculate reflection direction
    vec3 reflectDir = reflect(-lightDir, norm);

    // Specular light
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    // Combine light and color contributions
    vec3 result = specular + diffuse + ambient;
    fragColor = vec4(result, 1.0);
}