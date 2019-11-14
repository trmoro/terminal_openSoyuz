#include "ui/TextLetter.h"

//Constructor
TextLetter::TextLetter(glyph* g) : Mesh()
{
	Vertex* v00 = new Vertex(glm::vec3(g->xBearing, g->yOffset, 0), glm::vec3(0, 0, 1), glm::vec2(0.0f, g->uvY));
	Vertex* v01 = new Vertex(glm::vec3(g->width + g->xBearing, g->yOffset, 0), glm::vec3(0, 0, 1), glm::vec2(g->uvW, g->uvY));
	Vertex* v11 = new Vertex(glm::vec3(g->width + g->xBearing, g->height + g->yOffset, 0), glm::vec3(0, 0, 1), glm::vec2(g->uvW, g->uvY + g->uvH));
	Vertex* v10 = new Vertex(glm::vec3(g->xBearing, g->height + g->yOffset, 0), glm::vec3(0, 0, 1), glm::vec2(0.0f, g->uvY + g->uvH));

	m_g = g;

	addVertex(v00);
	addVertex(v01);
	addVertex(v11);
	addVertex(v10);

	addIndex(0);
	addIndex(1);
	addIndex(2);

	addIndex(0);
	addIndex(2);
	addIndex(3);

	compile();
}

//Destructor
TextLetter::~TextLetter()
{

}

//Get Glyph
glyph* TextLetter::getGlyph() const
{
	return m_g;
}