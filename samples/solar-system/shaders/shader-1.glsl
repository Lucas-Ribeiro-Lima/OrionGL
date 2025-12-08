#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 nPos;
layout (location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TextCoord;
out vec3 Normal;
out vec3 FragPosition;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   TextCoord = aTextCoord;
   FragPosition = vec3(model * vec4(aPos, 1.0));
   Normal = mat3(transpose(inverse(model))) * nPos;
}