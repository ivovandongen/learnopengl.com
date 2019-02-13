#version 330 core

out vec4 fragColor;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
} fs_in;

uniform sampler2D floorTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool blinn;
uniform bool gammaOn;

void main() {
     float gamma = gammaOn ? 2.2 : 1.0;

    vec3 color = texture(floorTexture, fs_in.texCoords).rgb;

    // ambient
    vec3 ambient = 0.05 * color;

    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);
    vec3 normal = normalize(fs_in.normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = pow((diff * color).rgb, vec3(gamma));

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    if(blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    } else {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }

    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    fragColor = vec4(ambient + diffuse + specular, 1.0);

    fragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));
}