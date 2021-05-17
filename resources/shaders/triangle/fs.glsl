#version 330 core

in vec3 outColor;
in vec2 outTex;

uniform sampler2D image;
uniform sampler2D image2;

uniform float mix_factor;

void main()
{
    //gl_FragColor = vec4(outColor, 1.0f);
    vec4 color = texture(image, outTex);
    vec4 color2 = texture(image2, outTex);
    gl_FragColor = mix(color, color2, mix_factor);
    //gl_FragColor = color;
}
