#pragma once
#pragma message("ui/TextLetter is defined")

#include "core/Font.h"

#include "type/Mesh.h"

class TextLetter : public Mesh
{
public:
	//Constructor / Destructor
	TextLetter(glyph* g);
	~TextLetter();

	//Get Glyph
	glyph* getGlyph() const;

private:
	glyph* m_g;
};