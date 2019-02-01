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
    vec3 position;
    vec3 direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

uniform vec3 viewPos;

void main() {

    // Light direction
    vec3 lightDir = normalize(light.position - fragPos);

    float theta = dot(lightDir, normalize(-light.direction));

    if (theta > light.cutOff) {
        // do lighting calculations

        // Ambient light
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

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

        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        diffuse  *= attenuation;
        specular *= attenuation;

        // Combine light and color contributions
        vec3 result = specular + diffuse + ambient;
        fragColor = vec4(result, 1.0);
    } else {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        fragColor = vec4(light.ambient * vec3(texture(material.diffuse, texCoords)), 1.0);
    }
}