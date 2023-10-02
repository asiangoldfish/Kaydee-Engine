// Basic texture shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec3 v_position;
out vec2 v_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void
main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform bool u_enableTexture;

void
main()
{
    if (u_enableTexture) {
        color = texture(u_texture, v_texCoord * 10) * u_color;
    } else {
        color = u_color;
    }
}