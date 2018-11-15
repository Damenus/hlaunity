#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include "hlaPlugin.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

typedef void (*Connect)();
//typedef void(*Connect2)();
typedef Square *(*GetSquare)();
typedef float (*GetSquareX)();
typedef float (*GetSquareY)();
typedef void (*SetSquareX)(float);
typedef void (*SetSquareY)(float);
typedef void(*UpdatePosition)();


int _tmain(int argc, _TCHAR* argv[])
{
	Connect _connect;
	//Connect2 _connect2;
	GetSquare _getSquare;
	GetSquareX _getSquareX;
	GetSquareY _getSquareY;
	SetSquareX _setSquareX;
	SetSquareY _setSquareY;
	UpdatePosition _updatePosition;

	bool running = true;
	char key_press;
	Square *mySquare = NULL;
	float step = 0.05;
		
	HINSTANCE hDll = LoadLibrary(L"hlaPlugin_x64.dll");

	if (hDll != NULL)
	{
		// jeœli wszystko posz³o dobrze, tutaj mo¿emy wywo³aæ jak¹œ funkcjê biblioteczn¹
		cout << "Loaded library HLA" << endl;
		_connect = (Connect)GetProcAddress(hDll, "Connect");
		_connect();

		_getSquare = (GetSquare)GetProcAddress(hDll, "GetSquare");
		_getSquareX = (GetSquareX)GetProcAddress(hDll, "GetSquareX");
		_getSquareY = (GetSquareY)GetProcAddress(hDll, "GetSquareY");
		_setSquareX = (SetSquareX)GetProcAddress(hDll, "SetSquareX");
		_setSquareY = (SetSquareY)GetProcAddress(hDll, "SetSquareY");
		_updatePosition = (UpdatePosition)GetProcAddress(hDll, "UpdatePosition");

		cout << "Position X: " << _getSquareX() << "; Position Y: " << _getSquareY() << ";" << endl;
		_setSquareX(1.0);
		_setSquareY(1.0);
		_updatePosition();
		cout << "Position X: " << _getSquareX() << "; Position Y: " << _getSquareY() << ";" << endl;
	
		//void* dd = (void*)_getSquare();
		//cout << (Square*)dd << endl;
		//cout << mySquare->PozX << " " << mySquare->PozY << endl;

	}
	else
	{
		cout << endl << "Not loaded library" << endl;
		getch();
		return 0;
	}

	while (running)
	{
		key_press = getch();
		switch (key_press)
		{
		case KEY_ESC:
			running = false;
			break;
		case KEY_UP:
			cout << endl << "Up" << endl; //key up
			_setSquareX(-step);
			_updatePosition();
			cout << "Position X: " << _getSquareX() << "; Position Y: " << _getSquareY() << ";" << endl;
			break;
		case KEY_DOWN:
			cout << endl << "Down" << endl;   // key down
			_setSquareX(step);
			_updatePosition();
			cout << "Position X: " << _getSquareX() << "; Position Y: " << _getSquareY() << ";" << endl;
			break;
		case KEY_RIGHT:
			cout << endl << "Right" << endl;  // key right
			_setSquareY(step);
			_updatePosition();
			cout << "Position X: " << _getSquareX() << "; Position Y: " << _getSquareY() << ";" << endl;
			break;
		case KEY_LEFT:
			cout << endl << "Left" << endl;  // key left
			_setSquareY(-step);
			_updatePosition();
			cout << "Position X: " << _getSquareX() << "; Position Y: " << _getSquareY() << ";" << endl;
			break;
		//	cout << "\t\t\tKEY Pressed-> \" " << key_press << " \" Ascii Value =  " << (int)key_press << "\n\n";
		}

	}

	return 0;
}
