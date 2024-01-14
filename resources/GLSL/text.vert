#version 330 core
layout(location=0) in vec4 pos_attr;
layout(location=1) in vec4 col_attr;

out vec4 col;

uniform mat4 matrix;

void main()
{
      col=col_attr;
      gl_Position=matrix*pos_attr;
}
