#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec4 aTint;

out vec2 texCoord;
out vec4 tint;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   texCoord = vec2(1.0, 1.0);
   tint = vec4(1.0, 1.0, 1.0, 1.0);
}