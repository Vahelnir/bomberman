#version 330 core

in vec2 textureCoordinates;

uniform sampler2D tile_texture;

out vec4 fragColor;

void main() {
    vec4 text = texture(tile_texture, textureCoordinates);
    vec3 mixed = mix(text.rgb, vec3(0, 0, 0), 0.0);
    fragColor = vec4(mixed, text.a);
}