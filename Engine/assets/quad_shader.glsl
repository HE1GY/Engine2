#type vertex
#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_tex_coord;

out vec2 v_tex_coord;
void main()
{
    v_tex_coord=a_tex_coord;
    gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
}



#type fragment
#version 460 core

in vec2 v_tex_coord;

uniform sampler2D u_texture;
uniform sampler2D u_texture2;

out vec4 color;

void main()
{
    color = mix(texture(u_texture2, v_tex_coord), texture(u_texture, v_tex_coord), 0.7);
    //color = vec4(v_tex_coord, 0, 1);
}
