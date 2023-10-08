// Basic texture shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in float a_texIndex;
layout(location = 4) in float a_tilingFactor;

out vec3 v_position;
out vec2 v_texCoord;
out vec4 v_color;
out float v_texIndex;
out float v_tilingFactor;

uniform mat4 u_viewProjection;

void main()
{
    v_color = a_color;
    v_texCoord = a_texCoord;
    v_texIndex = a_texIndex;
    v_tilingFactor = a_tilingFactor;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec4 v_color;
in float v_texIndex;
in float v_tilingFactor;

uniform sampler2D u_textures[32];


void main()
{
    color = texture(u_textures[int(v_texIndex)], v_texCoord * v_tilingFactor) * v_color;
}