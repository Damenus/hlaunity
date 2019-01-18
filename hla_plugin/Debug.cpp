#include "Debug.h"


bool Debug::initiated = false;
ofstream Debug::_log;

Debug::Debug()
{
}


Debug::~Debug()
{
}

void Debug::init(string fileName)
{
	_log.open(fileName);
	initiated=_log.is_open();
}

void Debug::close()
{
	_log.close();
}

void Debug::Log(string logMessage)
{
	if (initiated) {
		_log << logMessage.data() << endl;
		_log.flush();
	}
}

void Debug::Log(wstring logMessage)
{
	if (initiated) {
		_log << logMessage.data() << endl;
		_log.flush();
	}
}

void Debug::Log(string logMessage, int value)
{
	if (initiated) {
		_log << logMessage.data() << value << endl;
		_log.flush();
	}
}
void Debug::Log(string logMessage, float value)
{
	if (initiated) {
		_log << logMessage.data() << value << endl;
		_log.flush();
	}
}