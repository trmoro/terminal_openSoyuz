#pragma once
#pragma message ("terminal/Terminal Process is defined")

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "core/Process.h"
#include "core/Font.h"

#include "type/Shader.h"

#include "ui/TextSet.h"

class TerminalProcess : public Process
{
public:

	//Constructor and Destructor
	TerminalProcess();
	~TerminalProcess();

	//Init
	void init() override;

	//Update and Render
	void update() override;
	void render() override;

	Font* f;

	TextSet* ts;

	Shader* s;

	glm::mat4 pvm;
private:

	//Key Pushed Score
	int m_pushedScore;
};