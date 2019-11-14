#include "terminal/TextLine.h"

//Constructor
TextLine::TextLine(Font* f)
{
	setFont(f);
	m_mesh = new Mesh();

	m_sumDX		= 0;
	m_numGlyph	= 0;
	m_allDX		= std::vector<unsigned int>();
	m_allGlyph	= std::vector<int>();
}

//Destructor
TextLine::~TextLine()
{

}

//Set Font
void TextLine::setFont(Font* f)
{
	m_font = f;
}

//Get Font
Font* TextLine::getFont() const
{
	return m_font;
}

//Add single char as int
void TextLine::add(int i)
{
	//Get Glyph
	glyph* g = getFont()->getGlyph(i);

	//Add Glyph
	m_allGlyph.push_back(i);
	addGlyph(m_mesh, g, m_sumDX, 0, m_numGlyph);

	//Update Delta-X
	m_sumDX += g->xAdvance;
	m_allDX.push_back(g->xAdvance);

	//Increment the number of Glyph
	m_numGlyph++;

	//Compile
	m_mesh->compile();
}

//Add a whole string
void TextLine::add(std::string s)
{
	//Print Text
	for (unsigned int i = 0; i < s.size(); i++)
	{
		//Generate Letter
		int id = s.at(i);
		if (id < 0)
			id += 256;

		add(id);
	}
}

//Remove a single character
void TextLine::remove()
{
	//If there are any glyph
	if (m_numGlyph > 0)
	{
		//Reduce Delta-X
		m_sumDX -= m_allDX.at(m_allDX.size() - 1);
		m_allDX.pop_back();
		m_allGlyph.pop_back();
		m_numGlyph--;

		//Remove Glyph
		removeGlyph();

		//Compile
		m_mesh->compile();
	}
}

//Add Glyph
void TextLine::addGlyph(Mesh* m, glyph * g, unsigned int dX, unsigned int dY, unsigned int i)
{
	Vertex* v00 = new Vertex(glm::vec3(dX + g->xBearing,dY + g->yOffset,0), glm::vec3(0,0,1), glm::vec2(0.0f,g->uvY) );
	Vertex* v01 = new Vertex(glm::vec3(dX + g->width + g->xBearing,dY + g->yOffset,0), glm::vec3(0,0,1), glm::vec2(g->uvW,g->uvY) );
	Vertex* v11 = new Vertex(glm::vec3(dX + g->width + g->xBearing,dY + g->height + g->yOffset,0), glm::vec3(0,0,1), glm::vec2(g->uvW, g->uvY + g->uvH) );
	Vertex* v10 = new Vertex(glm::vec3(dX + g->xBearing,dY + g->height + g->yOffset,0), glm::vec3(0,0,1), glm::vec2(0.0f, g->uvY + g->uvH) );

	m->addVertex(v00);
	m->addVertex(v01);
	m->addVertex(v11);
	m->addVertex(v10);

	m->addIndex(0 + 4 * i);
	m->addIndex(1 + 4 * i);
	m->addIndex(2 + 4 * i);

	m->addIndex(0 + 4 * i);
	m->addIndex(2 + 4 * i);
	m->addIndex(3 + 4 * i);
}

//Remove Glyph
void TextLine::removeGlyph()
{
	//Remove the last 4 Vertices and 6 Indices
	m_mesh->popBackVertex(4);
	m_mesh->popBackIndex(6);
}

//To String
std::string TextLine::toString() const
{
	std::string str = "";

	for (int i : m_allGlyph)
		str += UnicodeToUTF8(i);

	return str;
}

//Render
void TextLine::render()
{
	m_mesh->render();
}

//Convert Unicode/Int Value into UTF8 character/string
//Source : https://stackoverflow.com/questions/19968705/unsigned-integer-as-utf-8-value
std::string TextLine::UnicodeToUTF8(unsigned int codepoint)
{
	std::string out;

	if (codepoint <= 0x7f)
		out.append(1, static_cast<char>(codepoint));
	else if (codepoint <= 0x7ff)
	{
		out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
		out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
	}
	else if (codepoint <= 0xffff)
	{
		out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
		out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
		out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
	}
	else
	{
		out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
		out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
		out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
		out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
	}
	return out;
}