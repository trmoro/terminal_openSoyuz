#include "core/IO.h"
#include "core/Root.h"

//Init IO List (Used to Retrieve IO through callback)
std::vector<IO*> IO::IO_LIST = std::vector<IO*>();

//Init GLEW / GLFW lock
bool IO::GLEW_INIT = false;
bool IO::GLFW_INIT = false;

//Create
IO::IO() : SType()
{
	//Set type
	type = "IO";

	//GLFW will be initialized by the first IO
	initGLFW();

	//Set Window Settings
	m_window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	setAsCurrentContext();

	//Set Callbacks
	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetCharCallback(m_window, characterCallback);
	glfwSetCursorPosCallback(m_window, cursorPositionCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetScrollCallback(m_window, scrollCallback);
	glfwSetDropCallback(m_window, dropCallback);

	//Add it to the IO_LIST
	IO_LIST.push_back(this);

	//GLEW will be initialized by the first IO
	initGLEW();

	//Default value
	resetKey();
	resetCharCode();
}

//Delete
IO::~IO()
{
	//Destroy Window
	glfwDestroyWindow(m_window);
}

//Set As Current Context
void IO::setAsCurrentContext() const
{
	glfwMakeContextCurrent(m_window);
}

//Window is closed ?
bool IO::windowIsClosed() const
{
	return glfwWindowShouldClose(m_window);
}

//Update
void IO::update() const
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

//Get Window
GLFWwindow * IO::getWindow() const
{
	return m_window;
}

//Get Window Size
glm::vec2 IO::getWindowSize()
{
	//Window must exist
	if (m_window != nullptr)
	{
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		return glm::vec2(width, height);
	}
	else
		return glm::vec2();
}

//Get Key  (key, scancode, action, mods)
glm::vec4 IO::getKey() const
{
	return m_key;
}

//Get Char Code
unsigned int IO::getCharCode() const
{
	return m_char;
}

//Get Mouse Position
glm::vec2 IO::getMousePosition() const
{
	return m_mousePos;
}

//Get Mouse Button (Button,Action,Mod)
glm::vec3 IO::getMouseButton() const
{
	return m_mouseButton;
}

//Get Mouse Scrolling
glm::vec2 IO::getScroll() const
{
	return m_scroll;
}

//Get Dropped Path
std::string IO::getDroppedPath() const
{
	return m_droppedPath;
}

//Set Window Title
void IO::setWindowTitle(std::string title)
{
	glfwSetWindowTitle(m_window, title.c_str());
}

//Key call back
void IO::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	retrieveIO(window)->m_key = glm::vec4(key, scancode, action, mods);
}

//Char call back
void IO::characterCallback(GLFWwindow * window, unsigned int codepoint)
{
	retrieveIO(window)->m_char = codepoint;
}

//Cursor Position Callback
void IO::cursorPositionCallback(GLFWwindow * window, double xpos, double ypos)
{
	retrieveIO(window)->m_mousePos = glm::vec2(xpos, ypos);
}

//Mouse Button Callback
void IO::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	retrieveIO(window)->m_mouseButton = glm::vec3(button, action, mods);
}

//ScrollCallback
void IO::scrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
	retrieveIO(window)->m_scroll = glm::vec2(xoffset, yoffset);
}

//Drop to the window callback
void IO::dropCallback(GLFWwindow * window, int count, const char ** path)
{
	retrieveIO(window)->m_droppedPath = *path;
}

//Retrieve IO with a glfw window
IO * IO::retrieveIO(GLFWwindow * window)
{
	//Search in IO list
	for (IO* io : IO_LIST)
	{
		if (io->getWindow() == window)
			return io;
	}

	return nullptr;
}

//Reset Key
void IO::resetKey()
{
	m_key = glm::vec4();
}

//Reset Char Code
void IO::resetCharCode()
{
	m_char = 0;
}

//Clear IO List
void IO::clearIOLIST()
{
	IO_LIST.clear();
}

//To String
std::string IO::print(std::string options) const
{
	return "IO : " + name;
}

//To String
std::string IO::toString(std::string options) const
{
	return "IO : " + name;
}

//Set With String
void IO::setWithString(std::string str)
{
}

//Init GLEW
void IO::initGLEW()
{
	if (!GLEW_INIT)
	{
		//Enable using OpenGL 3 or greater
		glewExperimental = GL_TRUE;

		GLenum err = glewInit();

		//Print Error
		if (GLEW_OK != err)
			std::cout << glewGetErrorString(err) << std::endl;

		//Print Version
		//std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

		//Set Lock as True
		GLEW_INIT = true;
	}
}

//Init GLFW
bool IO::initGLFW()
{
	if (!GLFW_INIT)
	{
		//Initialization gone wrong ?
		if (!glfwInit())
			return false;

		//Initialization gone well
		//Set OpenGL context to 3.3, Anti-aliazing : 12
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, 12);

		//Set lock as true
		GLFW_INIT = true;

		//Print
		//std::cout << "GLFW is initialized" << std::endl;
	}
	return true;
}