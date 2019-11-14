#include "core/Process.h"
#include "core/Root.h"

//Constructor
Process::Process() : SType()
{
	//Process must be inited by Root
	m_isInit = false;

	//Init Child Object

	//Clear Color
	m_clearColor = new SVec4(glm::vec4());
	m_clearColor->name = "clearColor";
	m_clearColor->setParent(this);

	//Objects
	m_objects = new SType();
	m_objects->name = "objects";
	m_objects->setParent(this);

	//Rendering -> default | glow | <name> -> clearColor | <op>
}

//Destructor
Process::~Process()
{
	delete m_io;
}

//Init
void Process::init()
{
	//Init
	m_io = new IO();
	m_io->setParent(this);
	m_io->name = "IO";
	m_io->setWindowTitle(name);

	m_isInit = true;
}

//Is Init ?
bool Process::isInit() const
{
	return m_isInit;
}

//Update
void Process::update()
{	
	//Reset Char
	getIO()->resetCharCode();
	
	//All update
	for (SType* st : getObjects())
		st->update();
}

//Render
void Process::render()
{
	getIO()->update();

	//Set GL View and Clear Option
	glClearColor(m_clearColor->value.x, m_clearColor->value.y, m_clearColor->value.z, m_clearColor->value.w);

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
}

//Set IO
void Process::setIO(IO* io)
{
	m_io = io;
}

//Get IO
IO* Process::getIO() const
{
	return m_io;
}

//Get Objects
std::vector<SType*> Process::getObjects() const
{
	return m_objects->getChildren();
}

//Add Objects
void Process::add(SType* st)
{
	//Process ? Add process objects
	if (st->type == "process")
	{
		Process* p = (Process*)st;
		for (SType* s : p->getObjects())
			add(s);
	}
	//Add
	else
	{
		//Move to Objects
		st->setParent(m_objects);

		//Create Config
		st->createConfig();
	}
}

//Print
std::string Process::print(std::string options) const
{
	return "";
}

//To String
std::string Process::toString(std::string options) const
{
	return "";
}

//Set With String
void Process::setWithString(std::string str)
{
	
}

//New
Process* Process::newType(std::vector<std::string> args)
{
	Process* p = new Process();
	p->name = "unnamed_process";

	//Name
	if (args.size() > 1)
		p->name = args[1];

	return p;
}