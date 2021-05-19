#version 330 core

in vec3 outColor;
in vec2 outTex;

uniform sampler2D image;

void main()
{
    //gl_FragColor = vec4(outColor, 1.0f);
    vec4 color = texture(image, outTex);
    gl_FragColor = color;
}
