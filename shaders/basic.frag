#version 450
layout(std140, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
    vec4 lightPos;
    vec4 lightColor;
    vec4 viewPos;
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(ubo.lightPos.xyz - fragPos);
    vec3 viewDir = normalize(ubo.viewPos.xyz - fragPos);
    
    // Ambient
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * ubo.lightColor.rgb;
    
    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ubo.lightColor.rgb;
    
    // Specular (Blinn-Phong)
    float specularStrength = 0.6;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * ubo.lightColor.rgb;
    
    // Texture
    vec4 texColor = texture(texSampler, fragTexCoord);
    
    // Combine
    vec3 result = (ambient + diffuse + specular) * fragColor * texColor.rgb;
    
    outColor = vec4(result, texColor.a);
}
