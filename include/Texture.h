#pragma once

class Texture
{
	unsigned int TEX = 0;
public:
	Texture(const char* texture);
	Texture(const char* texture, bool flip);
	unsigned int getTex() const;
};

