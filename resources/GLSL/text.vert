#version 430 core
layout(location=0) in vec3 a_pos;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_tex_coords;

out vec3 frag_normal;
out vec2 frag_tex_coords;

void main()
{
      frag_normal=a_normal;
      frag_tex_coords=a_tex_coords;
      gl_Position=vec4(a_pos,1.0);
}
