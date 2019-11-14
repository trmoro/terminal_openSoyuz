#include "terminal/TerminalProcess.h"

#include "core/Root.h"

//Constructor
TerminalProcess::TerminalProcess()
{
	//Rename
	name = "terminalProcess";

	//Init
	m_pushedScore = 0;
}

//Destructor
TerminalProcess::~TerminalProcess()
{
}

//Init
void TerminalProcess::init()
{
	//Base Init
	Process::init();

	//Rename Display
	m_io->setWindowTitle("OpenSoyuz Terminal");

	//Init Shader and Font TODO change
	s = new Shader();

	s->getVertex()->value = Root::loadFile("Resources/TextSet.vs");
	s->getFragment()->value = Root::loadFile("Resources/TextSet.fs");
	s->generate();

	s->name = "shader";
	s->setParent(this);

	f = new Font("Resources/consola.ttf", 20, 0, 255);

	//Init TextSet
	ts = new TextSet();
	ts->setFont(f);
	ts->setShader(s);

	//Add Color
	ts->addColor(1, glm::vec4(0, 0.6, 1, 1));
	ts->addColor(2, glm::vec4(0.2, 0.7, 1, 1));
	ts->addColor(3, glm::vec4(0.4, 1, 0.4, 1));
	ts->addColor(4, glm::vec4(1, 0.2, 0.7, 1));
	ts->addColor(5, glm::vec4(0.9, 0.2, 0.2, 1));

	//Add Token
	ts->addToken("openSoyuz", 1);
	for (std::string s : Root::getInstance()->getTokens())
		ts->addToken(s, 2);
	for (std::string s : Root::getInstance()->getObjectTypes())
		ts->addToken(s, 3);
	ts->addToken("exit", 5);

	//Add Presentation Text
	ts->add("Welcome to openSoyuz, tape your first command :\n" + Root::getInstance()->getWholePath());
	ts->setStateLastLine(1);

	//Set Init
	m_isInit = true;
}

//Update
void TerminalProcess::update()
{
	//Set Position
	ts->setPosition(glm::vec3(0, getIO()->getWindowSize().y - (ts->getLineNumber() * f->getTallest() * 1.2), 0));

	//Special Key (backslash, enter, ...)
	glm::vec4 key = m_io->getKey();

	//If a Key is pushed or holded
	if (key.z == 1 || key.z == 2)
	{
		//Key was released or pushed enough times
		if (m_pushedScore == 0 || (m_pushedScore > 30 && m_pushedScore % 2 == 0) )
		{
			//Backspace -> remove last char
			if (key.x == GLFW_KEY_BACKSPACE)
				ts->remove();
			//Enter
			else if (key.x == GLFW_KEY_ENTER)
			{
				//Analysis the last line (remove the first part (path>) )
				unsigned int partToRemove = Root::getInstance()->getWholePath().size();
				std::string str = ts->toStringLastLine();
				str = str.substr(partToRemove, str.size() - partToRemove);
				Root::getInstance()->analysis(str);

				//New Line
				ts->newLine();

				//Print unprinted line
				ts->add(Root::getInstance()->getUnprintedToPrint());
				ts->add(Root::getInstance()->getWholePath());
				ts->setStateLastLine(1);
			}
		}
		
		//Increase Pushed
		m_pushedScore++;
	}
	//Reset Pushed Score
	else
		m_pushedScore = 0;

	if (m_io->getCharCode() != 0)
		ts->add(m_io->getCharCode());

	m_io->resetCharCode();
}

//Render
void TerminalProcess::render()
{
	getIO()->update();

	pvm = glm::ortho(0.0f, m_io->getWindowSize().x, m_io->getWindowSize().y, 0.0f, -100.0f, 100.0f);

	//Set GL View and Clear Option
	glClearColor(0.0f, 0.0f, 0.05f, 1.0f);

	//How OpenGL Blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Depth Settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
		
	//No FrameBuffer, Update ViewPort and Clear
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_io->getWindowSize().x, m_io->getWindowSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update Matrix and Render
	ts->setProjView(pvm);
	ts->render();
}