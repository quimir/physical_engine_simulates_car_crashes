#version 430 core
out vec4 frag_color;

in vec3 frag_normal;
in vec2 frag_tex_coords;

void main()
{
      frag_color=vec4(1.0f,0.5f,0.2f,1.0f);
}
