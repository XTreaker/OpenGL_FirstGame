#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
#include <assert.h>



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) // https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window =(OWindow*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();

		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}

OWindow::OWindow()
{
	WNDCLASSEX wc = {}; // Contains window class information.
	wc.cbSize = sizeof(WNDCLASSEX); // The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEX). 
	wc.lpszClassName = L"OGL3DWindow"; // A pointer to a null-terminated string or is an atom.
	wc.lpfnWndProc = &WndProc; // A pointer to the window procedure.

	assert(RegisterClassEx(&wc));

	RECT rc = { 0, 0, 1024, 768 };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(NULL, L"OGL3DWindow", L"My first OpenGL 3D Game", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);
	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);
}

OWindow::~OWindow()
{
	DestroyWindow((HWND)m_handle);
}

void OWindow::onDestroy()
{
	m_handle = nullptr;
}

bool OWindow::isClosed()
{
	return !m_handle;
}
