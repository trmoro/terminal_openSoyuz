#pragma once
#pragma message("core/Font is defined")

#include <iostream>
#include <unordered_map>

#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

struct glyph
{
	float uvY;
	float uvW;
	float uvH;
	unsigned int width;
	unsigned int height;
	int xBearing;
	int xAdvance;
	int yOffset;
};

class Font
{
public:
	Font(std::string path, unsigned int size, unsigned int start, unsigned int end);
	~Font();
	GLuint getTexture() const;
	glyph* getGlyph(unsigned int id);

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getTallest() const;

	static void initFreeType();
	static void clearFreeType();
private:
	GLuint m_texture;

	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_tallest;

	std::unordered_map<unsigned int, glyph*> m_glyphs;
	static FT_Library fLib;
};