#version 330 core

in vec3 outColor;
in vec2 outTex;
in vec3 outNormal;

uniform int diffuse_size;

uniform vec3 lightColor;
uniform vec3 lightDirection;

uniform sampler2D diffuse[2];
uniform sampler2D specular[2];

void main()
{
    // 每个类型的贴图通常只有一个，暂时直接用一个
    vec4 color = texture(diffuse[0], outTex);
    // ambient color
    vec3 ambientColor = vec3(0.1, 0.1, 0.1) * color.rgb * lightColor;

    vec3 toLightDir = -normalize(lightDirection);
    float diffuseFactor = max(dot(toLightDir, normalize(outNormal)), 0);
    vec3 diffuseColor = diffuseFactor * color.rgb * lightColor;

    gl_FragColor = vec4(diffuseColor + ambientColor, 1.0);
}
