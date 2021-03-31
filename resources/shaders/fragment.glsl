#version 440

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D diffuseMap;
uniform vec4 custom_color;

void main() {
    fragColor = custom_color * texture(diffuseMap, texCoords);
}
