#version 330
layout(location = 0)in vec3 Position;
layout(location = 1)in vec3 Color;

out vec3 outColor;

uniform mat4 gWorld;

void main()
{
    gl_Position = gWorld * vec4(0.5 * Position, 1.0);
    outColor = Color;
}

