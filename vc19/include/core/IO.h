#pragma once
#pragma message ("core/IO is defined")

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "core/SType.h"

class IO : public SType
{
public:

	//Create and Delete
	IO();
	~IO();

	//Set As Current Context, OpenGL will now print in this IO
	void setAsCurrentContext() const;

	//Closed and Update
	bool windowIsClosed() const;
	void update() const;

	//Getters
	GLFWwindow* getWindow() const;
	glm::vec2 getWindowSize();

	//Get Key : x=Key z=Pushed/Realeased
	glm::vec4 getKey() const;

	unsigned int getCharCode() const;
	glm::vec2 getMousePosition() const;
	glm::vec3 getMouseButton() const;
	glm::vec2 getScroll() const;
	std::string getDroppedPath() const;

	//Setters
	void setWindowTitle(std::string title);

	//Reset
	void resetKey();
	void resetCharCode();

	//Clear IO List
	static void clearIOLIST();

	//To String and Set With String (Parent Function)
	std::string print(std::string options) const override;
	std::string toString(std::string options) const override;
	void setWithString(std::string str) override;

	//Init GLEW and GLFW
	void initGLEW();
	bool initGLFW();

private:

	//Window
	GLFWwindow* m_window;

	//Variable from Callback
	glm::vec4 m_key;
	glm::vec2 m_mousePos;
	glm::vec3 m_mouseButton;
	glm::vec2 m_scroll;

	unsigned int m_char;
	std::string m_droppedPath;

	//Callback
	static std::vector<IO*> IO_LIST;
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void dropCallback(GLFWwindow* window, int count, const char** paths);
	static IO* retrieveIO(GLFWwindow* window);

	//Locks : Only init GLEW and GLFW once
	static bool GLEW_INIT;
	static bool GLFW_INIT;
};