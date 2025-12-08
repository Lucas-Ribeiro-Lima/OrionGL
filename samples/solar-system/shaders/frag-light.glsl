#version 330 core

in vec2 TextCoord;

uniform sampler2D TextureData;

out vec4 FragColor;

void main()
{
	float bright = 1.0f;
    vec4 tex = texture(TextureData, TextCoord);

	FragColor = vec4(tex.rgb * bright, tex.a);
}