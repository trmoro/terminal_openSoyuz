#include "core/Root.h"

//Singleton
Root* Root::Instance = nullptr;

//Print
void print(std::string s)
{
	//Print Input
	if (Root::getInstance()->getCurrentObject() == nullptr)
		Root::getInstance()->printOutput(s + "\n");
	//Print type
	else if(s == "type")
		Root::getInstance()->printOutput(Root::getInstance()->getCurrentObject()->type + "\n");
	//Print Function
	else
		Root::getInstance()->printOutput(Root::getInstance()->getCurrentObject()->print(s) + "\n" );
}

//ToString
void toString(std::string s)
{
	//Print Input
	if (Root::getInstance()->getCurrentObject() == nullptr)
		Root::getInstance()->printOutput(s + "\n");
	//Print type
	else if (s == "type")
		Root::getInstance()->printOutput(Root::getInstance()->getCurrentObject()->type + "\n");
	//To String
	else
		Root::getInstance()->printOutput(Root::getInstance()->getCurrentObject()->toString(s) + "\n");
}

//Set
void set(std::string s)
{
	if (Root::getInstance()->getCurrentObject() != nullptr)
		Root::getInstance()->getCurrentObject()->setWithString(s);
}

//Add SType
void add(std::string s)
{
	//Split
	std::vector<std::string> args = Root::splitString(s, " ");

	//Only one argument, Operator onto Current Object
	if (args.size() == 1 && Root::getInstance()->getCurrentObject() != nullptr)
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then Add
		if (st != nullptr)
			Root::getInstance()->getCurrentObject()->add(st);
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A > B
	else if (args.size() == 3 && args[1] == ">")
	{
		//Find A
		SType* a = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//A is Found ?
		if (a != nullptr)
		{
			//Find B
			SType* b = Root::getInstance()->getObject(args[2], Root::getInstance()->getCurrentObject());

			//B is Found ?
			if (b != nullptr)
				b->add(a);
			else
				Root::getInstance()->printOutput("\n" + args[2] + " isn't found\n\n");
		}
		//A not Found
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A new B
	else if (args.size() == 3 && args[1] == "new")
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then RetAdd
		if (st != nullptr)
		{
			SType * nt = Root::getInstance()->getCurrentObject()->retAdd(st);
			nt->name = args[2];
			nt->setParent(Root::getInstance()->getCurrentObject());
		}
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");

	}
}

//Min SType
void min(std::string s)
{
	//Split
	std::vector<std::string> args = Root::splitString(s, " ");

	//Only one argument, Operator onto Current Object
	if (args.size() == 1 && Root::getInstance()->getCurrentObject() != nullptr)
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then Add
		if (st != nullptr)
			Root::getInstance()->getCurrentObject()->min(st);
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A > B
	else if (args.size() == 3 && args[1] == ">")
	{
		//Find A
		SType* a = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//A is Found ?
		if (a != nullptr)
		{
			//Find B
			SType* b = Root::getInstance()->getObject(args[2], Root::getInstance()->getCurrentObject());

			//B is Found ?
			if (b != nullptr)
				b->min(a);
			else
				Root::getInstance()->printOutput("\n" + args[2] + " isn't found\n\n");
		}
		//A not Found
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A new B
	else if (args.size() == 3 && args[1] == "new")
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then RetMin
		if (st != nullptr)
		{
			SType * nt = Root::getInstance()->getCurrentObject()->retMin(st);
			nt->name = args[2];
			nt->setParent(Root::getInstance()->getCurrentObject());
		}
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");

	}
}

//Multiply SType
void mul(std::string s)
{
	//Split
	std::vector<std::string> args = Root::splitString(s, " ");

	//Only one argument, Operator onto Current Object
	if (args.size() == 1 && Root::getInstance()->getCurrentObject() != nullptr)
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then Add
		if (st != nullptr)
			Root::getInstance()->getCurrentObject()->mul(st);
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A > B
	else if (args.size() == 3 && args[1] == ">")
	{
		//Find A
		SType* a = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//A is Found ?
		if (a != nullptr)
		{
			//Find B
			SType* b = Root::getInstance()->getObject(args[2], Root::getInstance()->getCurrentObject());

			//B is Found ?
			if (b != nullptr)
				b->mul(a);
			else
				Root::getInstance()->printOutput("\n" + args[2] + " isn't found\n\n");
		}
		//A not Found
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A new B
	else if (args.size() == 3 && args[1] == "new")
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then RetMul
		if (st != nullptr)
		{
			SType * nt = Root::getInstance()->getCurrentObject()->retMul(st);
			nt->name = args[2];
			nt->setParent(Root::getInstance()->getCurrentObject());
		}
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");

	}
}

//Divide SType
void div(std::string s)
{
	//Split
	std::vector<std::string> args = Root::splitString(s, " ");

	//Only one argument, Operator onto Current Object
	if (args.size() == 1 && Root::getInstance()->getCurrentObject() != nullptr)
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then Add
		if (st != nullptr)
			Root::getInstance()->getCurrentObject()->div(st);
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A > B
	else if (args.size() == 3 && args[1] == ">")
	{
		//Find A
		SType* a = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//A is Found ?
		if (a != nullptr)
		{
			//Find B
			SType* b = Root::getInstance()->getObject(args[2], Root::getInstance()->getCurrentObject());

			//B is Found ?
			if (b != nullptr)
				b->div(a);
			else
				Root::getInstance()->printOutput("\n" + args[2] + " isn't found\n\n");
		}
		//A not Found
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A new B
	else if (args.size() == 3 && args[1] == "new")
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then RetDiv
		if (st != nullptr)
		{
			SType * nt = Root::getInstance()->getCurrentObject()->retDiv(st);
			nt->name = args[2];
			nt->setParent(Root::getInstance()->getCurrentObject());
		}
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");

	}
}

//Modulo SType
void mod(std::string s)
{
	//Split
	std::vector<std::string> args = Root::splitString(s, " ");

	//Only one argument, Operator onto Current Object
	if (args.size() == 1 && Root::getInstance()->getCurrentObject() != nullptr)
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then Add
		if (st != nullptr)
			Root::getInstance()->getCurrentObject()->mod(st);
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A > B
	else if (args.size() == 3 && args[1] == ">")
	{
		//Find A
		SType* a = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//A is Found ?
		if (a != nullptr)
		{
			//Find B
			SType* b = Root::getInstance()->getObject(args[2], Root::getInstance()->getCurrentObject());

			//B is Found ?
			if (b != nullptr)
				b->mod(a);
			else
				Root::getInstance()->printOutput("\n" + args[2] + " isn't found\n\n");
		}
		//A not Found
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");
	}
	//3 Arguments : op A new B
	else if (args.size() == 3 && args[1] == "new")
	{
		//Find object
		SType* st = Root::getInstance()->getObject(args[0], Root::getInstance()->getCurrentObject());

		//If Found then RetMod
		if (st != nullptr)
		{
			SType * nt = Root::getInstance()->getCurrentObject()->retMod(st);
			nt->name = args[2];
			nt->setParent(Root::getInstance()->getCurrentObject());
		}
		else
			Root::getInstance()->printOutput("\n" + args[0] + " isn't found\n\n");

	}
}

//Edit
void edit(std::string s)
{
	Root::getInstance()->setEditMode(true);
	Root::getInstance()->setEditStorage("");
}

//Execute Script
void exec(std::string s)
{
	if (Root::getInstance()->getCurrentObject() != nullptr )
	{
		//Check current object
		if (Root::getInstance()->getCurrentObject()->type == "script")
		{
			SScript* s = (SScript*)Root::getInstance()->getCurrentObject();
			s->execute();
		}
		//Check current object children
		else
		{
			SType* st = Root::getInstance()->getObject(s, nullptr);
			//Found
			if (st != nullptr)
			{
				SScript* s = (SScript*)st;
				s->execute();
			}
			//Not found
			else
				Root::getInstance()->printOutput("\nNot found\n\n");

		}
		//
	}
}

//Execute File script
void execLoad(std::string s)
{
	std::ifstream inFile(s);
	if (inFile)
	{
		std::string line;
		while (std::getline(inFile, line))
			Root::getInstance()->analysis(line);
	}
	else
		Root::getInstance()->printOutput("\n\nERROR : Couldn't open file : " + s + "\n\n");
}

//Go
void go(std::string s)
{
	SType* st = Root::getInstance()->getObject(s,nullptr);

	//Object found
	if (st != nullptr)
		Root::getInstance()->setCurrentObject(st);
	//Not found
	else
		Root::getInstance()->printOutput("\nNot found\n\n");
}

//System
void system(std::string s)
{
	system(s.c_str());
}

//Rename
void rename(std::string s)
{
	if(Root::getInstance()->getCurrentObject() != nullptr)
		Root::getInstance()->getCurrentObject()->name = s;
}

//Go Back
void goBack(std::string s)
{
	if (Root::getInstance()->getCurrentObject()->getParent() != nullptr)
		Root::getInstance()->setCurrentObject(Root::getInstance()->getCurrentObject()->getParent());
	else
		Root::getInstance()->setCurrentObject(nullptr);
}

//List
void list(std::string s)
{
	//List children
	if (Root::getInstance()->getCurrentObject() != nullptr)
	{
		std::string out = "";
		for (SType* st : Root::getInstance()->getCurrentObject()->getChildren())
			if (st != nullptr)
				out += st->name + "\t";
		Root::getInstance()->printOutput(out + "\n");
	}
	//List Root objects if no current object
	else
	{
		std::string out = "";
		for (SType* st : Root::getInstance()->getObjects() )
			out += st->name + "\t";
		Root::getInstance()->printOutput(out + "\n");
	}
}

//Go To Object
void goTo(std::string s)
{
	//Not in Root::getInstance()
	if (Root::getInstance()->getCurrentObject() != nullptr)
	{
		SType* newCurrent = nullptr;

		for (SType* st : Root::getInstance()->getCurrentObject()->getChildren())
			if (st != nullptr && st->name == s)
				newCurrent = st;

		if (newCurrent != nullptr)
			Root::getInstance()->setCurrentObject(newCurrent);
	}

	//In Root::getInstance()
	else
	{
		SType* newCurrent = nullptr;

		for (SType* st : Root::getInstance()->getObjects() )
			if (st != nullptr && st->name == s)
				newCurrent = st;

		if (newCurrent != nullptr)
			Root::getInstance()->setCurrentObject(newCurrent);
	}
}

//New
void rootNew(std::string s)
{
	//Split
	std::vector<std::string> str = Root::splitString(s, " ");

	//New Objects
	SType* no = nullptr;

	//Set as current
	bool sac = false;

	//New Process
	if (str[0] == "process")
	{
		Process* p = Process::newType(str);
		Root::getInstance()->addProcess(p);
		no = p;
		sac = true;
	}

	//Other object type
	else
		no = Root::getInstance()->newObject(str);

	//Set Parent of new object : Add Object to Root or Current Object
	if (Root::getInstance()->getCurrentObject() != nullptr)
		no->setParent(Root::getInstance()->getCurrentObject());
	else
		Root::getInstance()->addObject(no);

	//Set Current Object
	if (sac)
		Root::getInstance()->setCurrentObject(no);
}

//Set Project Name
void projectName(std::string s)
{
	Root::getInstance()->setProjectName(s);
}

//Use Object Inner Function
void use(std::string s)
{
	if (Root::getInstance()->getCurrentObject() != nullptr)
		Root::getInstance()->getCurrentObject()->use(s);
}

//Sort
void sort(std::string s)
{
	if (Root::getInstance()->getCurrentObject() != nullptr)
		Root::getInstance()->getCurrentObject()->sortChildren("abc");

}

//Root Init
void Root::init()
{
	//Set Current Object to null
	m_currentObject = nullptr;

	//Init variables
	m_projectName	= "NewProject";
	m_logIn			= std::vector<std::string>();
	m_logOut		= std::vector<std::string>();
	m_printedLine	= 0;
	m_editOn		= false;

	//Init Objects and Tokens
	m_objects	= std::vector<SType*>();
	m_processes = std::vector<Process*>();
	m_tokenMap	= std::map<std::string, void(*)(std::string)>();
	m_objectMap	= std::map<std::string, SType*(*)(std::vector<std::string>)>();

	//Add Token Function
	m_tokenMap["go"]			= go;
	m_tokenMap["add"]			= add;
	m_tokenMap["min"]			= min;
	m_tokenMap["mul"]			= mul;
	m_tokenMap["div"]			= div;
	m_tokenMap["mod"]			= mod;
	m_tokenMap["new"]			= rootNew;
	m_tokenMap["set"]			= set;
	m_tokenMap["use"]			= use;
	m_tokenMap["sort"]			= sort;
	m_tokenMap["list"]			= list;
	m_tokenMap["goto"]			= goTo;
	m_tokenMap["edit"]			= edit;
	m_tokenMap["exec"]			= exec;
	m_tokenMap["print"]			= print;
	m_tokenMap["rename"]		= rename;
	m_tokenMap["goback"]		= goBack;
	m_tokenMap["system"]		= system;
	m_tokenMap["execload"]		= execLoad;
	m_tokenMap["toString"]		= toString;
	m_tokenMap["projectname"]	= projectName;

	//Add Object to create
	m_objectMap["object"]	= SType::newType;
	m_objectMap["pointer"]	= SPointer::newType;
	m_objectMap["int"]		= SInt::newType;
	m_objectMap["float"]	= SFloat::newType;
	m_objectMap["bool"]		= SBool::newType;
	m_objectMap["text"]		= SText::newType;
	m_objectMap["vec4"]		= SVec4::newType;
	m_objectMap["vec3"]		= SVec3::newType;
	m_objectMap["vec2"]		= SVec2::newType;
	m_objectMap["mat4"]		= SMat4::newType;
	m_objectMap["mat3"]		= SMat3::newType;
	m_objectMap["mat2"]		= SMat2::newType;
	m_objectMap["vertex"]	= Vertex::newType;
	m_objectMap["mesh"]		= Mesh::newType;
	m_objectMap["model"]	= Model::newType;

	//Freetype
	Font::initFreeType();
}

////////////////////////////////////Root Inner Code

//Root Constructor
Root::Root()
{
	//Set Singleton
	Root::Instance = this;

	//Init
	init();

	//String Catching inputs
	std::string s = "";

	//Soyuz Engine Presentation
	std::cout << "*************************\n**                     **\n**      OpenSoyuz      **\n**                     **\n*************************\n" << std::endl;

	//Create a terminal
	TerminalProcess* tp = new TerminalProcess();
	addProcess(tp);
	addObject(tp);

	//Continue until a process exist
	m_continue = true;
	m_exit = false;
	while (m_continue && !m_exit)
	{
		//By default, stop Soyuz after the loop if no process has been updated/rendered
		m_continue = false;

		//Update / Render all processes
		for (unsigned int i = 0; i < m_processes.size(); i++)
		{
			Process* p = m_processes[i];

			//If Process isn't null and not closed
			if (p != nullptr && (!p->isInit() || !p->getIO()->windowIsClosed()) )
			{
				//Process init ?
				if (!p->isInit())
					p->init();

				//Set Process IO Current, and Update/Render Process
				p->getIO()->setAsCurrentContext();
				p->update();
				p->render();
				m_continue = true;
			}
			//If Process isn't null but closed
			else if(p != nullptr)
			{
				if (m_currentObject == p)
					m_currentObject = nullptr;

				delete p;
				m_processes[i] = nullptr;
			}
			//
		}

	}
}

//Delete
Root::~Root()
{
	//End all Process
	for (Process* p : m_processes)
	{
		if (p != nullptr)
			delete p;
	}

	//Clear FreeType
	Font::clearFreeType();
}

//Get Current Object
SType* Root::getCurrentObject() const
{
	return m_currentObject;
}

//Set Current Object
void Root::setCurrentObject(SType * s)
{
	m_currentObject = s;
}

//Get Objects
std::vector<SType*> Root::getObjects() const
{
	return m_objects;
}

//Add Object to Root
void Root::addObject(SType * st)
{
	m_objects.push_back(st);
}

//Get Current Path
std::string Root::getObjectPath(SType* s) const
{
	if (s->getParent() != nullptr)
		return getObjectPath(s->getParent()) + "." + s->name;
	return "." + s->name;
}

//Get Object with path
SType * Root::getObject(std::string path, SType* cur) const
{
	/*
	if(cur != nullptr)
		std::cout << path << " : " << cur->name << std::endl;
	else
		std::cout << path << std::endl;
	*/

	//Absolute Path ?
	bool abs = false;
	if (path[0] == '.')
		abs = true;

	/*
	if(abs)
		std::cout << "abs " << abs << std::endl;
	else
		std::cout << "!abs " << abs << std::endl;
	*/

	//Split
	std::vector<std::string> str = splitString(path, ".");

	//If Absolute, look for Root's objects
	if (abs)
	{
		//std::cout << str[1] << " : " << path.erase(0, str[1].size() + 1) << std::endl;

		//We use str[1], because [0] is empty, because first char is the spliting separator
		//str[1].size() + 2 because we remove the '/' before and after the process
		for (SType* p : m_objects)
		{
			//Return next SType
			if (p->name == str[1] && str.size() > 2)
				return getObject(path.erase(0, str[1].size() + 2), p);
			//Return process
			else if(p->name == str[1])
				return p;
		}

	}
	else
	{
		//If no current object in the method, use current object of Root
		if (cur == nullptr && m_currentObject != nullptr)
		{
			for(SType* s : m_currentObject->getChildren() )
			{
				//Found the next element
				if (s->name == str[0] && str.size() > 1)
					return getObject(path.erase(0, str[0].size() + 1), s);
				//Found the final element
				else if (s->name == str[0])
					return s;
			}
		}
		//Current object of the method
		else if(cur != nullptr)
		{
			for (SType* s : cur->getChildren())
			{
				//Found the next element
				if (s->name == str[0] && str.size() > 1)
					return getObject(path.erase(0, str[0].size() + 1), s);
				//Found the final element
				else if(s->name == str[0])
					return s;
			}
		}
		//Else look for root
		else
		{
			for (SType* s : m_objects)
			{
				//Found the next element
				if (s->name == str[0] && str.size() > 1)
					return getObject(path.erase(0, str[0].size() + 1), s);
				//Found the final element
				else if (s->name == str[0])
					return s;
			}
		}

	}

	//If not found, return null
	return nullptr;
}

//Analyse String from Terminal
void Root::analysis(std::string line)
{
	//Exit
	if (line == "exit")
		m_exit = true;
	//Analyse
	else
	{
		//Detect first space
		std::string token = "";
		std::string value = "";
		bool tokenTaken = false;
		for (unsigned int i = 0; i < line.size(); i++)
		{
			if (!tokenTaken && line[i] != ' ')
				token.push_back(line[i]);
			else if (!tokenTaken && line[i] == ' ')
				tokenTaken = true;
			else
				value.push_back(line[i]);
		}

		//Add to Input Log
		m_logIn.push_back(line);

		//Execute line
		execute(token, value);
	}
}

//Execute Token
void Root::execute(std::string token, std::string value)
{
	//Find Token
	std::map<std::string, void(*)(std::string)>::iterator it;
	it = m_tokenMap.find(token);

	//Token Exists
	if (it != m_tokenMap.end())
		m_tokenMap[token](value);
}

//Add Process
void Root::addProcess(Process* p)
{
	m_processes.push_back(p);
}

//Get Processes
std::vector<Process*> Root::getProcesses() const
{
	return m_processes;
}

//Print Output
void Root::printOutput(std::string str)
{
	//Add to output log
	m_logOut.push_back(str);
}

//Get Unprinted Line to Print
std::string Root::getUnprintedToPrint()
{
	std::string str = "";
	while (m_printedLine < m_logOut.size())
	{
		str += m_logOut[m_printedLine];
		m_printedLine++;
	}

	return str;
}

//Print to Console un-printed line
void Root::printToConsole()
{
	bool first = true;
	while (m_printedLine < m_logOut.size())
	{
		if (!first)
			std::cout << std::endl;
		else
			first = false;
		std::cout << m_logOut[m_printedLine];
		m_printedLine++;
	}
}

//Set Edit Mode
void Root::setEditMode(bool b)
{
	m_editOn = b;
}

//Get Edit Mode
bool Root::getEditMode() const
{
	return m_editOn;
}

//Set Edit Storage
void Root::setEditStorage(std::string s)
{
	m_editStorage = s;
}

//Get Edit Storage
std::string Root::getEditStorage() const
{
	return m_editStorage;
}

//Get Project Name
std::string Root::getProjectName() const
{
	return m_projectName;
}

//Get Whole Path + > sign
std::string Root::getWholePath() const
{
	if (getCurrentObject() == nullptr)
		return getProjectName() + ">";
	else
		return getProjectName() + getObjectPath(getCurrentObject()) + ">";
}

//Set Project Name
void Root::setProjectName(std::string s)
{
	m_projectName = s;
}

//Get Tokens
std::vector<std::string> Root::getTokens()
{
	//Store all tokens
	std::vector<std::string> tokens = std::vector<std::string>();

	//Read all key of the token map
	std::map<std::string, void(*)(std::string)>::iterator it;
	for (it = m_tokenMap.begin(); it != m_tokenMap.end(); it++)
		tokens.push_back(it->first);

	//Return
	return tokens;
}

//Get Objects Type
std::vector<std::string> Root::getObjectTypes()
{
	//Store all tokens
	std::vector<std::string> otype = std::vector<std::string>();
	otype.push_back("process");

	//Read all key of the token map
	std::map<std::string, SType*(*)(std::vector<std::string>)>::iterator it;
	for (it = m_objectMap.begin(); it != m_objectMap.end(); it++)
		otype.push_back(it->first);

	//Return
	return otype;
}

//New Object
SType* Root::newObject(std::vector<std::string> args)
{
	//Find Object Type
	std::map<std::string, SType*(*)(std::vector<std::string>)>::iterator it;
	it = m_objectMap.find(args[0]);

	//Type Exists
	if (it != m_objectMap.end())
		return m_objectMap[args[0]](args);
}

//Split String
std::vector<std::string> Root::splitString(std::string str, std::string sep)
{
	//Vector of string that will be returned
	std::vector<std::string> res;

	//String in which will be stored current part
	std::string val = "";

	//Cursor in the Separator
	unsigned int sI = 0;

	//Read String
	for (unsigned int i = 0; i < str.length(); i++)
	{
		//If is the same char that the separator cursor
		if (sI < sep.length() && str[i] == sep[sI])
			sI++;
		//Reset separator cursor
		else
			sI = 0;

		//Add to current part
		val += str[i];

		//The separator is read
		if (sI == sep.length())
		{
			//Remove Separator and add it to the vector
			res.push_back(val.substr(0, val.length() - sep.length()));

			//Reset current part and separator cursor
			val = "";
			sI = 0;
		}
	}

	//Add last part
	if (val != "")
		res.push_back(val);

	return res;
}

//Split Multiple String into one
std::vector<std::string> Root::splitStrings(std::vector<std::string> strs, std::string sep)
{
	//Vector of string that will be returned
	std::vector<std::string> res;

	//Get all 'spliting'
	for (std::string str : strs)
	{
		std::vector<std::string> tmpSplit = Root::splitString(str,sep);
		for (std::string s : tmpSplit)
			res.push_back(s);
	}

	//Return
	return res;
}

//Load File
std::string Root::loadFileLineFeed(std::string path, const char * lineFeed)
{
	std::string out = "";

	std::ifstream inFile(path);
	if (inFile)
	{
		std::string line;
		while (std::getline(inFile, line))
			out += line + lineFeed;
	}
	else
		Root::getInstance()->printOutput("ERROR : Couldn't open file : " + path);

	return out;
}

std::string Root::loadFile(std::string path)
{
	return loadFileLineFeed(path, "\n");
}

//Get  Singleton Instance
Root* Root::getInstance()
{
	return Instance;
}