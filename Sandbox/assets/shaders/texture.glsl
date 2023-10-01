// Basic texture shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec3 v_position;
out vec2 v_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main() {
    v_texCoord = a_texCoord;
    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec3 u_color;
uniform sampler2D u_texture;

void main() {
    //color = vec4(v_texCoord, 0.0, 1.0);
    color = texture(u_texture, v_texCoord) * vec4(u_color, 1.0);
}