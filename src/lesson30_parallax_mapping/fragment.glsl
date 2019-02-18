#version 330 core
out vec4 fragColor;

in VS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 tangentLightPos;
    vec3 tangentViewPos;
    vec3 tangentFragPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float heightScale;

uniform vec3 lightPos;
uniform vec3 viewPos;

vec2 parallaxMapping(vec2 texCoords, vec3 viewDir) {
    float height =  texture(depthMap, texCoords).r;
    vec2 p = viewDir.xy / viewDir.z * (height * heightScale);
    return texCoords - p;
}

void main() {

    // offset texture coordinates with Parallax Mapping
    vec3 viewDir = normalize(fs_in.tangentViewPos - fs_in.tangentFragPos);
    vec2 texCoords = parallaxMapping(fs_in.texCoords,  viewDir);

    if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;

     // obtain normal from normal map in range [0,1]
    vec3 normal  = texture(normalMap, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    // get diffuse color
    vec3 color = texture(diffuseMap, texCoords).rgb;

    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.tangentLightPos - fs_in.tangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    fragColor = vec4(ambient + diffuse + specular, 1.0);
}