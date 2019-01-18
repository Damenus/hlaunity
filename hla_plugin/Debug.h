#pragma once
#include <fstream>

using namespace std;
class Debug
{
public:
	Debug();
	~Debug();
	public:
		static void init(string fileName);
		static void close();
		static void Log(string logMessage);
		static void Log(wstring logMessage);
		static void Log(string logMessage, int value);
		static void Log(string logMessage, float value);
		static ofstream _log;
		static bool initiated;
};

