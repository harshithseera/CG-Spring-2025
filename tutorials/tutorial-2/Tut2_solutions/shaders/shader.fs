#version 330
in vec3 outColor;
layout(location = 0) out vec4 diffuseColor;

void main()
{
    diffuseColor =  vec4(outColor, 1.0);
}
