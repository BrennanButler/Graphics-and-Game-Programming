#include "Systemclass.h"

SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

void SystemClass::Shutdown()
{
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	if(m_Graphics)
	{
		delete m_Graphics;
		m_Graphics = 0;
	}

	ShutdownWindows();
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	applicationHandle = NULL;

}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;

	InitializeWindows(screenWidth, screenHeight);

	m_Input = new InputClass;

	if(!m_Input)
	{
		return false;
	}

	m_Input->Initialize();

	m_Graphics = new GraphicsClass;

	if(!m_Graphics)
	{
		return false;
	}

	if(!(m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd)))
	{
		return false;
	}

}

void SystemClass::InitializeWindows(int &width, int &height)
{
	WNDCLASSEX wc;
	int posX, posY;

	applicationHandle = this;

	m_applicationName = "RastertekEngine";

	m_hinstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	if(!RegisterClassEx(&wc))
		MessageBox(NULL, "Cannot register window class.", "ERROR", MB_OK);

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	width = 800;
	height = 600;

	posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
				WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				posX, posY, width, height, NULL, NULL, m_hinstance, NULL);

	if(!m_hwnd)
		MessageBox(NULL, "Failed to create window.", "ERROR", MB_OK);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);

}

void SystemClass::Run()
{
	MSG msg = {0};

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(msg.message == WM_QUIT)
				break;
		}
		else 
		{
			Frame();
		}
	}
}

bool SystemClass::Frame()
{
	if(!m_Graphics->Frame())
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		case WM_KEYDOWN:
			MessageBox(NULL, "keydown", "key", MB_OK);

		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return applicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}