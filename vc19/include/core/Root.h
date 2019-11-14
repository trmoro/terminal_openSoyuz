#pragma once
#pragma message ("core/Root is defined")

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <map>

#include "core/SType.h"
#include "core/Process.h"
#include "core/Font.h"

#include "type/BaseType.h"
#include "type/VecType.h"
#include "type/MatType.h"
#include "type/Vertex.h"
#include "type/Mesh.h"
#include "type/SScript.h"
#include "type/Model.h"
#include "type/Shader.h"
#include "type/Camera.h"

#include "terminal/TerminalProcess.h"

class Root
{
public:
	//Constructor / Destructor
	Root();
	~Root();

	//Init
	void init();

	//Analysis and Execute
	void analysis(std::string line);
	void execute(std::string token, std::string value);

	//Current Object
	SType* getCurrentObject() const;
	void setCurrentObject(SType* s);

	//Objects
	std::vector<SType*> getObjects() const;
	void addObject(SType* st);

	std::string getObjectPath(SType* s) const;
	SType* getObject(std::string path, SType* cur) const;

	//Process
	void addProcess(Process* p);
	std::vector<Process*> getProcesses() const;

	//Print Output
	void printOutput(std::string str);
	void printToConsole();
	std::string getUnprintedToPrint();

	//Set EditMode and Storage
	void setEditMode(bool b);
	bool getEditMode() const;
	void setEditStorage(std::string s);
	std::string getEditStorage() const;

	//Project Name
	std::string getProjectName() const;
	std::string getWholePath() const;
	void setProjectName(std::string s);

	//Get Tokens
	std::vector<std::string> getTokens();
	std::vector<std::string> getObjectTypes();

	//New Object
	SType* newObject(std::vector<std::string> str);

	//Split String
	static std::vector<std::string> splitString(std::string str, std::string sep);
	static std::vector<std::string> splitStrings(std::vector<std::string> strs, std::string sep);

	//Load File
	static std::string loadFile(std::string path);
	static std::string loadFileLineFeed(std::string path, const char * lineFeed);

	//Root Singleton Access
	static Root* getInstance();

private:

	//Token Map
	std::map<std::string, void(*)(std::string)> m_tokenMap;
	
	//Object Map
	std::map<std::string, SType*(*)(std::vector<std::string>)> m_objectMap;

	//Current Object
	SType* m_currentObject;

	//Objects and Processes
	std::vector<SType*>	m_objects;
	std::vector<Process*> m_processes;

	//Editing mode
	bool m_editOn;
	std::string m_editStorage;

	//Logs, printed line, and printing mode
	std::vector<std::string> m_logIn;
	std::vector<std::string> m_logOut;
	unsigned int m_printedLine;

	//Project Name
	std::string m_projectName;
	
	//Continue Soyuz ?
	bool m_continue;
	bool m_exit;

	//Root Singleton
	static Root* Instance;
};