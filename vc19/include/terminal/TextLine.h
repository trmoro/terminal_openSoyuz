#pragma once
#pragma message("terminal/Text Line is defined")

#include "core/Font.h"

#include "type/Mesh.h"

class TextLine
{
public:
	//Constructor and Destructor
	TextLine(Font* f);
	~TextLine();

	//Render
	void render();

	//Set / Get Font
	void setFont(Font* f);
	Font* getFont() const;

	//Add
	void add(int i);
	void add(std::string s);

	//Remove
	void remove();

	//To String
	std::string toString() const;

private:
	
	static std::string UnicodeToUTF8(unsigned int codepoint);

	void addGlyph(Mesh* m, glyph * g, unsigned int dX, unsigned int dY, unsigned int i);
	void removeGlyph();

	unsigned int m_sumDX, m_numGlyph;
	std::vector<unsigned int> m_allDX;

	std::vector<int> m_allGlyph;

	Mesh* m_mesh;
	Font* m_font;
};