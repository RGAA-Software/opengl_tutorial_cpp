#version 330 core

in vec3 outColor;
in vec2 outTex;
in vec3 outNormal;
in vec3 outPos;

uniform sampler2D image;

uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform vec3 cameraPosition;

void main()
{
    //gl_FragColor = vec4(outColor, 1.0f);
    vec4 color = texture(image, outTex);

    // ambient
    vec3 ambient = vec3(0.1, 0.1, 0.1);
    vec3 ambientColor = ambient * lightColor * color.rgb;

    // diffuse
    vec3 toLightDir = -normalize(lightDirection);
    float cosTheta = dot(toLightDir, normalize(outNormal));
    float diffuseFactor = max(cosTheta, 0);
    vec3 diffuseColor = lightColor * color.rgb * diffuseFactor;

    // specular
    vec3 reflectDir = normalize(reflect(-toLightDir, outNormal));
    vec3 toCameraDir = normalize(cameraPosition - outPos);
    float specularFactor = pow(max(dot(reflectDir, toCameraDir), 0), 128);
    vec3 specularColor = lightColor * color.rgb * specularFactor * 1;

    vec3 lightEffectedColor = (diffuseColor + specularColor);

    gl_FragColor = vec4(ambientColor + lightEffectedColor, 1.0);
}
