#version 330 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

// required when using a perspective projection matrix
float linearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main() {             
    float depthValue = texture(depthMap, texCoords).r;
    // fragColor = vec4(vec3(linearizeDepth(depthValue) / far_plane), 1.0); // perspective
    fragColor = vec4(vec3(depthValue), 1.0); // orthographic
}