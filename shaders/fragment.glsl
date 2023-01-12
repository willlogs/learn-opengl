#version 330 core

in vec3 color;
in vec2 uv;

uniform sampler2D main_map;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0f) * texture(main_map, uv);
} 