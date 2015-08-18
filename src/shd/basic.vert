#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureInput;

uniform mat4 transform;

out vec2 finalTextCoords;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
    finalTextCoords = vec2(textureInput.x, 1.0f - textureInput.y);
}