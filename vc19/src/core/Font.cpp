#include "core/Font.h"

//Font Library
FT_Library Font::fLib(0);

//Create
Font::Font(std::string path, unsigned int size, unsigned int start, unsigned int end)
{
	//Initialize Face
	FT_Face face;
	if (FT_New_Face(fLib, path.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	FT_Set_Pixel_Sizes(face, 0, size);

	//Init Variable
	m_width = 0;
	m_height = 0;
	m_tallest = 0;

	m_glyphs = std::unordered_map<unsigned int, glyph*>();
	std::vector<unsigned char> glyphsData = std::vector<unsigned char>();

	//First Pass : Determine Width and Height
	for (unsigned int i = start; i <= end; i++)
	{
		//Load
		if (FT_Load_Glyph(face, FT_Get_Char_Index(face, i), FT_LOAD_RENDER))
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
			std::cout << "ERROR::FREETYPE: Failed to render Glyph" << std::endl;

		//Set Width and Height
		if (m_width < face->glyph->bitmap.width)
			m_width = face->glyph->bitmap.width;
		if (m_tallest < face->glyph->bitmap.rows)
			m_tallest = face->glyph->bitmap.rows;
		m_height += face->glyph->bitmap.rows;

		glyph* g = new glyph{ 0, (float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap_left, face->glyph->advance.x / 64, face->glyph->bitmap_top };
		m_glyphs[i] = g;

		//std::cout << "Index " << g.id << " : ";
		for (unsigned int a = 0; a < (g->width * g->height); a++)
			glyphsData.push_back(*(face->glyph->bitmap.buffer + a));
	}

	//Second Pass : Generate Data
	unsigned char* fontData = new unsigned char[m_width * m_height];
	for (unsigned int i = 0; i < (m_width * m_height); i++)
		fontData[i] = 0;

	unsigned int z = 0;
	unsigned int iData = 0;
	for (unsigned int i = 0; i < m_glyphs.size(); i++)
	{
		//Draw on texture
		glyph* g = m_glyphs[i];
		for (unsigned int y = 0; y < g->height; y++)
		{
			for (unsigned int x = 0; x < g->width; x++)
			{
				//Insert
				fontData[x + ((y + z)*m_width)] = glyphsData.at(iData);
				iData++;
			}
		}
		//Update Glyph Data
		g->uvY = (float)z / (float)m_height;
		g->uvH /= (float)m_height;
		g->uvW /= (float)m_width;
		g->yOffset = m_tallest - g->yOffset;

		z += g->height;
	}

	//We're done with freetype
	FT_Done_Face(face);

	//Storing Mode
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Generate Texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, fontData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Initial Storing Mode
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	//Clear Data
	delete[] fontData;
}

//Delete
Font::~Font()
{
}

//Get Texture
GLuint Font::getTexture() const
{
	return m_texture;
}

//Get Glyph
glyph* Font::getGlyph(unsigned int id)
{
	return m_glyphs[id];
}

//Get Widht
unsigned int Font::getWidth() const
{
	return m_width;
}

//Get Height
unsigned int Font::getHeight() const
{
	return m_height;
}

//Get Tallest value
unsigned int Font::getTallest() const
{
	return m_tallest;
}

//Init FreeType
void Font::initFreeType()
{
	//Initialize FreeType
	if (FT_Init_FreeType(&fLib))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
}

//Clear FreeType
void Font::clearFreeType()
{
	FT_Done_FreeType(Font::fLib);
}