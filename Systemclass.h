#ifndef _SYSTEMCLASS_H_
#define	_SYSTEMCLASS_H_

#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>


//Input & Graphics

#include "Inputclass.h"
#include "Graphicsclass.h"


class SystemClass {

public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
	bool Initialize();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	void Shutdown();

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	

private:
	HWND m_hwnd;
	HINSTANCE m_hinstance;
	LPCSTR m_applicationName;
	InputClass* m_Input;
	GraphicsClass* m_Graphics;

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* applicationHandle = 0;

#endif