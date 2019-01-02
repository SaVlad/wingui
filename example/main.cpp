#define WG_USING_ALL
#include <wingui.h>
#include <tchar.h>

bool CALLBACK mdcb(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl) {
	_tprintf(_T("[0x%X] %s\n"), window->GetHandle(), window->GetText().c_str());
	_tputs(_T("Mouse down"));
	if (HASFLAG(button, MouseButton::LeftButton))
		_tprintf(_T("Left "));
	if (HASFLAG(button, MouseButton::MiddleButton))
		_tprintf(_T("Middle "));
	if (HASFLAG(button, MouseButton::RightButton))
		_tprintf(_T("Right "));
	if (HASFLAG(button, MouseButton::XButton1))
		_tprintf(_T("X1 "));
	if (HASFLAG(button, MouseButton::XButton2))
		_tprintf(_T("X2 "));
	if (shift)
		_tprintf(_T("Shift "));
	if (ctrl)
		_tprintf(_T("Ctrl "));
	_tprintf(_T("\nPos: %d, %d\n"), x, y);
	return false;
}
bool CALLBACK closecb(Window*window) {
	_tprintf(_T("[0x%X] %s\n"), window->GetHandle(), window->GetText().c_str());
	_tputs(_T("Close"));
	return false;
}
bool CALLBACK destroycb(Window*window) {
	_tprintf(_T("[0x%X] %s\n"), window->GetHandle(), window->GetText().c_str());
	_tputs(_T("Destroy"));
	return false;
}
bool CALLBACK quitcb(Window*window, DWORD code) {
	_tprintf(_T("[0x%X] %s\n"), window->GetHandle(), window->GetText().c_str());
	_tprintf(_T("Quit %d"), code);
	return false;
}

void main() {
	try {
		Window*window = new Window(WindowStyle::HasCaption|WindowStyle::HasWindowMenu);
		WindowEventListener*el = new WindowEventListener();
		el->SetMouseDownCallback(mdcb);
		el->SetCloseCallback(closecb);
		el->SetDestroyCallback(destroycb);
		el->SetQuitCallback(quitcb);
		window->SetEventListener(el);
		window->SetText(_T("Test Window"));
		window->Show();
		window->MessagePump();
	}
	catch (InvalidHandleException*) {
		puts("Invalid handle exception occured");
	}
	catch (Win32Exception*w32e) {
		puts("Win32 exception occured");
		_tprintf(_T("[0x%X] %s\n"), w32e->GetCode(), w32e->GetDescription().c_str());
	}
}