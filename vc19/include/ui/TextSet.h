#pragma once
#pragma message("ui/TextSet is defined")

#include <list>
#include <map>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "core/Font.h"

#include "type/Shader.h"

#include "TextLetter.h"

//Line
struct TS_Line
{
	std::list<TextLetter*> letters;
	std::list<unsigned int> lettersID;
	std::list<unsigned int> lettersState;
	std::list<unsigned int> lettersColor;
};

class TextSet
{
public:
	//Constructor / Destructor
	TextSet();
	~TextSet();

	//Add
	void add(unsigned int i);
	void add(std::string str);

	//Remove
	void remove();

	//New Line
	void newLine();

	//To String
	std::string toStringLine(TS_Line* l) const;
	std::string toString() const;
	std::string toStringLastLine() const;

	//Render
	void render();

	//Set Font
	void setFont(Font* f);

	//Set Shader
	void setShader(Shader* s);

	//Set ProjView Matrix
	void setProjView(glm::mat4 projView);

	//Apply Token
	void applyToken(TS_Line* l);

	//Extract Token with a starting and ending char
	std::vector<std::string> extractRangeToken(TS_Line* l, char start, char end);

	//Set a Range on the last line
	void setLastLineRangeToken(char start, char end, unsigned int color_index);

	//Add Token / Color
	void addToken(std::string token, unsigned int index);
	void addTempToken(std::string token, unsigned int index);
	void addColor(unsigned int index, glm::vec4 color);

	//Set State
	void setState(TS_Line* l, unsigned int state);
	void setStateLastLine(unsigned int state);

	//Set / Get Position
	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition() const;

	//Get Line Number
	unsigned int getLineNumber() const;

private:

	//Convert Int to Unicode
	static std::string UnicodeToUTF8(unsigned int codepoint);

	//Lines of text
	std::list<TS_Line*> m_lines;

	//Token/Color Index
	std::map<std::string, unsigned int> m_tokenIndexMap;
	std::map<std::string, unsigned int> m_tmpTokenIndexMap;

	//Index/Color Map
	std::map<unsigned int, glm::vec4> m_indexColorMap;

	//Font and Shader
	Font* m_font;
	Shader* m_shader;

	//ProjView Matrix
	glm::mat4 m_projView;

	//Position
	glm::vec3 m_position;
};