#version 330

in vec2 uv;
out vec3 color;

uniform sampler2D image;

void main() {
    color = texture(image, uv).rgb;
}
