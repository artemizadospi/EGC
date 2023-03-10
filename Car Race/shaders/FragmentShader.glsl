#version 330

// Input
in vec3 color;

// Output
out vec4 out_color;


void main()
{
    out_color = vec4(color, 1);

}
