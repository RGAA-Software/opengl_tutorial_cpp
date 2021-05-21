#version 330 core

in vec3 outColor;
in vec2 outTex;
in vec3 outNormal;
in vec3 outPos;

uniform sampler2D image;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float lightCutoffAngel;
uniform float lightOuterCutoffAngel;

uniform vec3 cameraPosition;


void main()
{

    //gl_FragColor = vec4(outColor, 1.0f);
    vec4 color = texture(image, outTex);

    // ambient
    vec3 ambient = vec3(0.2, 0.2, 0.2);
    vec3 ambientColor = ambient * lightColor * color.rgb;

    vec3 lightDir = normalize(outPos - lightPosition);

    vec3 toLightDir = -lightDir;
    float diffuseFactor = max( dot(toLightDir, outNormal), 0);
    vec3 diffuseColor = diffuseFactor * color.rgb * lightColor;

    vec3 reflectDir = normalize(reflect(lightDir, outNormal));
    vec3 toCameraDir = normalize(cameraPosition - outPos);
    float specularFactor = pow( max( dot(reflectDir, toCameraDir), 0), 128);
    vec3 specluarColor = color.rgb * lightColor * specularFactor;

    float angel = dot(lightDirection, lightDir);
    if (angel > lightCutoffAngel) {
        // normal lighting ...
        gl_FragColor = vec4(diffuseColor + ambientColor + specluarColor, 1.0);
    } else {
        float distance = lightCutoffAngel - lightOuterCutoffAngel;
        float factor = 1 - clamp(((lightCutoffAngel - angel) / distance), 0, 1);
        gl_FragColor = vec4(ambientColor + (diffuseColor + specluarColor) * factor, 1.0);
    }

}
