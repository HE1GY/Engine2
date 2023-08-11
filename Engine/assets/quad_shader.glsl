#type vertex
#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_tex_coord;

uniform mat4 u_projection_view;
uniform mat4 u_transform;

out vec2 v_tex_coord;
void main()
{
    v_tex_coord=a_tex_coord;
    gl_Position = u_projection_view * u_transform * vec4(a_position.x, a_position.y, a_position.z, 1.0);
}



#type fragment
#version 460 core

in vec2 v_tex_coord;

uniform vec4 u_color;
uniform sampler2D u_texture;

out vec4 color;

void main()
{
    color = texture(u_texture, v_tex_coord) * vec4(u_color);
    //color = vec4(v_tex_coord, 0, 1);
}
