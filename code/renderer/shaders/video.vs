#version 330

in vec2 vertex;
out vec2 uv;

void main() 
{
    uv = vertex;
    gl_Position = vec4(2.0 * vertex.x - 1.0, 1.0 - 2.0 * vertex.y, 0.0, 1.0);
}
