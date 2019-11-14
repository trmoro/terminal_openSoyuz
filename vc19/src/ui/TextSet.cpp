#include "ui/TextSet.h"

//Included for Spliting
#include "core/Root.h"

//Constructor
TextSet::TextSet()
{
	//Init Lines and create a new line
	m_lines = std::list<TS_Line*>();
	newLine();

	//Set 3D
	m_projView = glm::mat4();
	m_position = glm::vec3();

	//Init Token/Index and Index/Color Map
	m_tokenIndexMap		= std::map<std::string, unsigned int>();
	m_tmpTokenIndexMap	= std::map<std::string, unsigned int>();
	m_indexColorMap		= std::map<unsigned int, glm::vec4>();

	m_indexColorMap[0] = glm::vec4(0.8, 0.8, 0.8, 1);
}

//Destructor
TextSet::~TextSet()
{

}

//Add to the back
void TextSet::add(unsigned int i)
{
	m_lines.back()->letters.push_back(new TextLetter(m_font->getGlyph(i)));
	m_lines.back()->lettersID.push_back(i);
	m_lines.back()->lettersState.push_back(0);
	m_lines.back()->lettersColor.push_back(0);

	applyToken(m_lines.back());
}

//Add string to the back
void TextSet::add(std::string str)
{
	//Read all letter of the string
	for (unsigned int i = 0; i < str.size(); i++)
	{
		//New Line ?
		if (str.at(i) == '\n')
			newLine();
		//New Letter
		else
		{
			int id = str.at(i);
			if (id < 0)
				id += 256;

			add(id);
		}

		//
	}
}

//Remove to the back
void TextSet::remove()
{
	//Remove the last letter of the line
	if (m_lines.size() > 0 && m_lines.back()->letters.size() > 0 )
	{
		//The letter is removable ?
		if (m_lines.back()->lettersState.back() == 0)
		{
			m_lines.back()->letters.pop_back();
			m_lines.back()->lettersID.pop_back();
			m_lines.back()->lettersState.pop_back();
			m_lines.back()->lettersColor.pop_back();

			applyToken(m_lines.back());
		}
	}
	//If no letter, remove the last line and remove the last letter
	else if (m_lines.size() > 1 )
	{
		m_lines.pop_back();
		remove();
	}
}

//New Line
void TextSet::newLine()
{
	m_lines.push_back(new TS_Line{ std::list<TextLetter*>(), std::list<unsigned int>(), std::list<unsigned int>(), std::list<unsigned int>() });
}

//To String a single Line
std::string TextSet::toStringLine(TS_Line* l) const
{
	std::string str = "";

	for (unsigned int i : l->lettersID)
		str += UnicodeToUTF8(i);

	return str;

}

//To String
std::string TextSet::toString() const
{
	std::string str = "";

	for (TS_Line* l : m_lines)
		str += toStringLine(l) + "\n";

	return str;
}

//To String Last Line
std::string TextSet::toStringLastLine() const
{
	return toStringLine(m_lines.back());
}


//Render
void TextSet::render()
{
	//Use Shader and Font Texture
	glUseProgram(m_shader->getID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_font->getTexture());

	//Set Texture
	m_shader->setUniformi( (GLchar*) "m_texture", 0);

	//Delta X and Delta Y
	double dX = 0;
	double dY = 0;

	//Render all lines
	for (TS_Line* l : m_lines)
	{
		//Render the line
		std::list<unsigned int>::iterator colorIte = l->lettersColor.begin();
		for (TextLetter* tl : l->letters)
		{
			//Set Matrix, Color and Render
			glm::mat4 pvm = m_projView * glm::translate(glm::mat4(1.0f), (glm::vec3(dX,dY,0)+m_position) );
			m_shader->setUniformMatrix4((GLchar*) "ProjViewModel", pvm);
			m_shader->setUniformVec4((GLchar*) "m_color", m_indexColorMap[*colorIte]);
			tl->render();

			//New Letter
			dX += tl->getGlyph()->xAdvance;

			//Increment Color Iterator
			colorIte++;
		}

		//New Line
		dX = 0;
		dY += m_font->getTallest() * 1.2;
	}

	//Unbind Shader and Font Texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

//Convert Unicode/Int Value into UTF8 character/string
//Source : https://stackoverflow.com/questions/19968705/unsigned-integer-as-utf-8-value
std::string TextSet::UnicodeToUTF8(unsigned int codepoint)
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

//Apply Token
void TextSet::applyToken(TS_Line* l)
{
	//Convert line to unicode
	std::string str = toStringLine(l);

	//Reset to 0
	std::list<unsigned int>::iterator colorIteStart;
	for (colorIteStart = l->lettersColor.begin(); colorIteStart != l->lettersColor.end(); colorIteStart++)
		*colorIteStart = 0;

	//Read Token/Index Map
	std::map<std::string, unsigned int>::iterator it;
	for (it = m_tokenIndexMap.begin(); it != m_tokenIndexMap.end(); it++)
	{
		//Search Token
		size_t pos = str.find(it->first);
		while (pos != std::string::npos)
		{
			//Colorize, to modify, we erase and insert

			//Erase
			std::list<unsigned int>::iterator colorIteStart, colorIteEnd;
			colorIteStart = colorIteEnd = l->lettersColor.begin();
			advance(colorIteStart, pos);
			advance(colorIteEnd, pos + it->first.size() );
			l->lettersColor.erase(colorIteStart,colorIteEnd);

			//Insert (Token Size)times the Index
			colorIteStart = l->lettersColor.begin();
			advance(colorIteStart, pos);
			l->lettersColor.insert(colorIteStart, it->first.size(), it->second);

			//Search for the same token 
			pos = str.find(it->first, pos + it->first.size());
		}
	}

	//Read Temporary Token/Index Map
	for (it = m_tmpTokenIndexMap.begin(); it != m_tmpTokenIndexMap.end(); it++)
	{
		//Search Token
		size_t pos = str.find(it->first);
		while (pos != std::string::npos)
		{
			//Colorize, to modify, we erase and insert

			//Erase
			std::list<unsigned int>::iterator colorIteStart, colorIteEnd;
			colorIteStart = colorIteEnd = l->lettersColor.begin();
			advance(colorIteStart, pos);
			advance(colorIteEnd, pos + it->first.size());
			l->lettersColor.erase(colorIteStart, colorIteEnd);

			//Insert (Token Size)times the Index
			colorIteStart = l->lettersColor.begin();
			advance(colorIteStart, pos);
			l->lettersColor.insert(colorIteStart, it->first.size(), it->second);

			//Search for the same token 
			pos = str.find(it->first, pos + it->first.size());
		}
	}
	//Clean Temporary map
	m_tmpTokenIndexMap.clear();

	//
}

//Extract Token with a staring and ending string Range
std::vector<std::string> TextSet::extractRangeToken(TS_Line* l, char start, char end)
{
	//Tokens
	std::vector<std::string> tokens = std::vector<std::string>();

	//Convert line to unicode
	std::string str = toStringLine(l);

	//While we find starting char
	size_t start_pos = str.find(start);
	while (start_pos != std::string::npos)
	{
		//Find Ending char
		size_t end_pos = str.find(end, start_pos + 1);

		//Get Tokens
		tokens.push_back(str.substr(start_pos, end_pos) );

		//Search Next Starting token
		start_pos = str.find(start);
	}

	//Return
	return tokens;

}

//Set a Range on the last line
void TextSet::setLastLineRangeToken(char start, char end, unsigned int color_index)
{
	for (std::string t : extractRangeToken(m_lines.back(), start, end))
		addTempToken(t, color_index);
}

//Add Token
void TextSet::addToken(std::string token, unsigned int index)
{
	m_tokenIndexMap[token] = index;
}

//Add Temporary Token
void TextSet::addTempToken(std::string token, unsigned int index)
{
	m_tmpTokenIndexMap[token] = index;
}

//Add Color
void TextSet::addColor(unsigned int index, glm::vec4 color)
{
	m_indexColorMap[index] = color;
}

//Set State
void TextSet::setState(TS_Line* l,unsigned int state)
{
	std::list<unsigned int>::iterator it;
	for (it = l->lettersState.begin(); it != l->lettersState.end(); it++)
		*it = state;
}

//Set State Last Line
void TextSet::setStateLastLine(unsigned int state)
{
	setState(m_lines.back(), state);
}

//Set Font
void TextSet::setFont(Font* f)
{
	m_font = f;
}

//Set Shader
void TextSet::setShader(Shader* s)
{
	m_shader = s;
}

//Set ProjView Matrix
void TextSet::setProjView(glm::mat4 projView)
{
	m_projView = projView;
}

//Set Position
void TextSet::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

//Get Position
glm::vec3 TextSet::getPosition() const
{
	return m_position;
}

//Get Line Number
unsigned int TextSet::getLineNumber() const
{
	return m_lines.size();
}