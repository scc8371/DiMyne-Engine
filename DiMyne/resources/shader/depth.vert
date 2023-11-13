#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec4 aTint;
layout (location = 3) in vec3 aNormal;

out vec2 texCoord;
out vec4 tint;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
   FragPos = vec3(model * vec4(aPos, 1));
   texCoord = aTex;
   tint = aTint;
   Normal = mat3(transpose(inverse(model))) * aNormal;
   gl_Position = projection * view * vec4(FragPos, 1.0); 
}