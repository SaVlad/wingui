#include <algorithm>
#include <time.h>
#include <tchar.h>
#include "wg_window.h"
#include "wg_exceptions.h"
#define CHECKCB(x) if(x == nullptr) return false; else return x

LPCTSTR GetRandomString(int len) {
	static bool init = false;
	static const TCHAR alpha[] = _T("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	if (!init)
		srand(time(NULL));
	LPTSTR str = new TCHAR[len + 1];
	for (int i = 0; i < len; ++i)
		str[i] = alpha[rand() % 62];
	str[len] = 0;
	return str;
}

void RunCallbacks(wg::controls::Window*window, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (window)
		window->OnMessage(uMsg, wParam, lParam);
}

LRESULT CALLBACK WG_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	wg::controls::Window*window = (wg::controls::Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (uMsg == WM_CREATE) {
		LPCREATESTRUCT create = (LPCREATESTRUCT)lParam;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)create->lpCreateParams);
	}
	if (window && window->OnMessage(uMsg, wParam, lParam))
		return 0;
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

namespace wg::controls {
	Window::Window() : Window(WindowStyle::WSDefault) {}
	Window::Window(WindowStyle wstyle) : Window(wstyle, WindowClassStyle::MoveSizeRedraw) {}
	Window::Window(WindowClassStyle wcstyle) : Window(WindowStyle::WSDefault, wcstyle) {}
	Window::Window(WindowStyleEx wexstyle) : Window(WindowStyle::WSDefault, wexstyle, WindowClassStyle::MoveSizeRedraw) {}
	Window::Window(WindowStyle wstyle, WindowStyleEx wexstyle) : Window(wstyle, wexstyle, WindowClassStyle::MoveSizeRedraw) {}
	Window::Window(WindowStyle wstyle, WindowClassStyle wcstyle) : Window(wstyle, WindowStyleEx::WSEXDefault, wcstyle) {}
	Window::Window(WindowStyleEx wexstyle, WindowClassStyle wcstyle) : Window(WindowStyle::WSNone, wexstyle, wcstyle) {}
	Window::Window(WindowStyle wstyle, WindowStyleEx wexstyle, WindowClassStyle wcstyle) : Control(), el(nullptr) {
		class_name = GetRandomString(12);
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WNDCLASSEX c;
		c.cbSize = sizeof(WNDCLASSEX);
		c.style = wcstyle;
		c.lpfnWndProc = WG_WindowProc;
		c.cbClsExtra = 0;
		c.cbWndExtra = 0;
		c.hInstance = hInstance;
		c.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		c.hCursor = LoadCursor(NULL, IDC_ARROW);
		c.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		c.lpszMenuName = NULL;
		c.lpszClassName = class_name;
		c.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		wg::exceptions::assert_win32(RegisterClassEx(&c));
		handle = CreateWindowEx(
			wexstyle, class_name, _T("New window"),
			wstyle, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
			NULL, NULL, hInstance, this
		);

	}
	Window::~Window() {
		for (auto it = children.begin(); it != children.end(); ++it)
			delete *it;
		children.clear();
	}

	void Window::BringToTop() {
		check_handle();
		wg::exceptions::assert_win32(BringWindowToTop(handle));
	}
	void Window::Close() {
		CloseWindow(handle);
		delete this;
	}
	SIZE Window::GetClientSize() const {
		SIZE sz;
		GetClientSize((int*)&sz.cx, (int*)&sz.cy);
		return sz;
	}
	void Window::GetClientSize(int*w, int*h) const {
		check_handle();
		RECT r;
		wg::exceptions::assert_win32(GetClientRect(handle, &r));
		*w = (int)r.right - r.left;
		*h = (int)r.bottom - r.top;
	}
	void Window::SetClientSize(SIZE sz) {
		SetClientSize(sz.cx, sz.cy);
	}
	void Window::SetClientSize(int w, int h) {
		int ww, wh, cw, ch, dw, dh;
		GetSize(&ww, &wh);
		GetClientSize(&cw, &ch);
		dw = (ww - cw) / 2;
		dh = (wh - ch) / 2;
		SetSize(w + dw, h + dh);
	}
	bool Window::IsMinimized() const {
		check_handle();
		bool ret = IsIconic(handle);
		wg::exceptions::assert_win32_maybe();
		return ret;
	}
	void Window::AddChild(Control*ctrl) {
		children.push_back(ctrl);
		SetParent(ctrl->GetHandle(), handle);
	}
	Control*Window::RemoveChild(Control*ctrl) {
		children.erase(std::remove(children.begin(), children.end(), ctrl), children.end());
		SetParent(ctrl->GetHandle(), NULL);
		return ctrl;
	}
	Control*Window::RemoveChild(int index) {
		Control*ctrl = children.at(index);
		children.erase(children.begin() + index);
		SetParent(ctrl->GetHandle(), NULL);
		return ctrl;
	}
	int Window::GetChildAmount() const {
		return children.size();
	}
	int Window::GetAllChild(Control**childs, int size) const {
		if (size == 0) return 0;
		int s = GetChildAmount();
		int m = s < size ? s : size;
		for (int i = 0; i < m; ++i)
			childs[i] = children.at(i);
		return m;
	}
	Control*Window::GetChild(int index) const {
		return children.at(index);
	}
	void Window::Hide() {
		check_handle();
		ShowWindow(handle, SW_HIDE);
		wg::exceptions::assert_win32_maybe();
	}
	void Window::Show() {
		check_handle();
		ShowWindow(handle, SW_SHOW);
		wg::exceptions::assert_win32_maybe();
	}
	void Window::Maximize() {
		check_handle();
		ShowWindow(handle, SW_MAXIMIZE);
		wg::exceptions::assert_win32_maybe();
	}
	void Window::Minimize() {
		check_handle();
		ShowWindow(handle, SW_MINIMIZE);
		wg::exceptions::assert_win32_maybe();
	}
	void Window::Restore() {
		check_handle();
		ShowWindow(handle, SW_RESTORE);
		wg::exceptions::assert_win32_maybe();
	}
	void Window::MessagePump() {
		check_handle();
		MSG msg;
		BOOL bRet;
		while ((bRet = GetMessage(&msg, handle, 0, 0)) != 0) {
			if (bRet == -1)
				return;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	bool Window::OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (el) return el->RunMessage(this, uMsg, wParam, lParam);
		return false;
	}
	WindowEventListener*Window::SetEventListener(WindowEventListener*listener) {
		WindowEventListener*old = el;
		el = listener;
		return old;
	}
	WindowEventListener*Window::GetEventListener() const {
		return el;
	}

	WindowEventListener::WindowEventListener() :
		Close(nullptr), Create(nullptr), Destroy(nullptr), EnabledChanged(nullptr),
		SizeMoveStarted(nullptr), SizeMoveEnded(nullptr), Moved(nullptr), Moving(nullptr),
		Ping(nullptr), Quit(nullptr), VisibleChanging(nullptr), SizeChanged(nullptr),
		SizeChanging(nullptr), UserChanged(nullptr), MouseLost(nullptr), MouseDown(nullptr),
		MouseUp(nullptr), MouseDouble(nullptr), MouseCaptured(nullptr), MouseLeft(nullptr),
		MouseHover(nullptr), MouseHWheel(nullptr), MouseWheel(nullptr), MouseMove(nullptr),
		ActiveChanged(nullptr), AppCommandCb(nullptr), Char(nullptr), DeadChar(nullptr),
		Hotkey(nullptr), KeyDown(nullptr), KeyUp(nullptr), ClipboardUpdate(nullptr) {}
	bool WindowEventListener::RunMessage(Window*window, UINT uMsg, WPARAM wParam, LPARAM lParam) const {
		LPCREATESTRUCT lpcs;
		WindowCreateEventArgs wcea;
		LPRECT r;
		MouseButton mb;
		LONG x, y, w, h;
		bool ret, shift, ctrl, ext, alt, prev, state;
		AppCommandSource src;
		WORD rep;
		AppCommand cmd;

		switch (uMsg) {
		case WM_CLOSE: CHECKCB(Close)(window);
		case WM_CREATE:
			lpcs = (LPCREATESTRUCT)lParam;
			wcea.Height = lpcs->cy;
			wcea.Width = lpcs->cx;
			wcea.X = lpcs->x;
			wcea.Y = lpcs->y;
			wcea.Title = _tstring(lpcs->lpszName);
			CHECKCB(Create)(window, wcea);
		case WM_DESTROY: CHECKCB(Destroy)(window);
		case WM_ENABLE: CHECKCB(EnabledChanged)(window, wParam == TRUE);
		case WM_ENTERSIZEMOVE: CHECKCB(SizeMoveStarted)(window);
		case WM_EXITSIZEMOVE: CHECKCB(SizeMoveEnded)(window);
		case WM_MOVE: CHECKCB(Moved)(window, LOWORD(lParam), HIWORD(lParam));
		case WM_MOVING:
			r = (LPRECT)lParam;
			CHECKCB(Moving)(window, &r->left, &r->top);
		case WM_NULL: CHECKCB(Ping)(window);
		case WM_QUIT: CHECKCB(Quit)(window, (DWORD)wParam);
		case WM_SHOWWINDOW: CHECKCB(VisibleChanging)(window, wParam == TRUE, (VisibleChangingStatus)lParam);
		case WM_SIZE: CHECKCB(SizeChanged)(window, (ResizeType)wParam, LOWORD(lParam), HIWORD(lParam));
		case WM_SIZING:
			r = (LPRECT)lParam;
			if (SizeChanging == nullptr) return false;
			ret = SizeChanging(window, (ResizingEdge)wParam, &x, &y, &w, &h);
			r->left = x;
			r->top = y;
			r->right = x + w;
			r->bottom = y + h;
			return ret;
		case WM_USERCHANGED: CHECKCB(UserChanged)(window);
		case WM_CAPTURECHANGED: CHECKCB(MouseLost)(window);
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_XBUTTONDOWN:
			mb = (MouseButton)(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (wParam & MK_SHIFT) == MK_SHIFT;
			ctrl = (wParam & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseDown)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl);
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP:
			mb = (MouseButton)(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (wParam & MK_SHIFT) == MK_SHIFT;
			ctrl = (wParam & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseUp)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl);
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_XBUTTONDBLCLK:
			mb = (MouseButton)(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (wParam & MK_SHIFT) == MK_SHIFT;
			ctrl = (wParam & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseDouble)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl);
		case WM_MOUSEACTIVATE: CHECKCB(MouseCaptured)(window);
		case WM_MOUSEHOVER:
			mb = (MouseButton)(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (wParam & MK_SHIFT) == MK_SHIFT;
			ctrl = (wParam & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseHover)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl);
		case WM_MOUSEHWHEEL:
			mb = (MouseButton)(LOWORD(wParam) & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (LOWORD(wParam) & MK_SHIFT) == MK_SHIFT;
			ctrl = (LOWORD(wParam) & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseHWheel)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl, HIWORD(wParam));
		case WM_MOUSELEAVE: CHECKCB(MouseLeft)(window);
		case WM_MOUSEMOVE:
			mb = (MouseButton)(wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (wParam & MK_SHIFT) == MK_SHIFT;
			ctrl = (wParam & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseMove)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl);
		case WM_MOUSEWHEEL:
			mb = (MouseButton)(LOWORD(wParam) & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (LOWORD(wParam) & MK_SHIFT) == MK_SHIFT;
			ctrl = (LOWORD(wParam) & MK_CONTROL) == MK_CONTROL;
			CHECKCB(MouseWheel)(window, mb, LOWORD(lParam), HIWORD(lParam), shift, ctrl, HIWORD(wParam));
		case WM_ACTIVATE: CHECKCB(ActiveChanged)(window, (ActivateType)wParam);
		case WM_APPCOMMAND:
			cmd = (AppCommand)GET_APPCOMMAND_LPARAM(lParam);
			src = (AppCommandSource)GET_DEVICE_LPARAM(lParam);
			mb = (MouseButton)(GET_KEYSTATE_LPARAM(lParam) & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2));
			shift = (GET_KEYSTATE_LPARAM(lParam) & MK_SHIFT) == MK_SHIFT;
			ctrl = (GET_KEYSTATE_LPARAM(lParam) & MK_CONTROL) == MK_CONTROL;
			CHECKCB(AppCommandCb)(window, cmd, src, mb, shift, ctrl);
		case WM_CHAR:
			rep = (lParam >> 0) & 0xFF;
			ext = ((lParam >> 24) & 0x01) == 0x01;
			alt = ((lParam >> 29) & 0x01) == 0x01;
			prev = ((lParam >> 30) & 0x01) == 0x01;
			state = ((lParam >> 31) & 0x01) == 0x01;
			CHECKCB(Char)(window, wParam, rep, ext, alt, prev, state);
		case WM_DEADCHAR:
			rep = (lParam >> 0) & 0xFF;
			ext = ((lParam >> 24) & 0x01) == 0x01;
			alt = ((lParam >> 29) & 0x01) == 0x01;
			prev = ((lParam >> 30) & 0x01) == 0x01;
			state = ((lParam >> 31) & 0x01) == 0x01;
			CHECKCB(DeadChar)(window, wParam, rep, ext, alt, prev, state);
		case WM_HOTKEY: CHECKCB(Hotkey)(window, wParam);
		case WM_KEYDOWN:
			rep = (lParam >> 0) & 0xFF;
			ext = ((lParam >> 24) & 0x01) == 0x01;
			alt = ((lParam >> 29) & 0x01) == 0x01;
			prev = ((lParam >> 30) & 0x01) == 0x01;
			state = ((lParam >> 31) & 0x01) == 0x01;
			CHECKCB(KeyDown)(window, wParam, rep, ext, alt, prev, state);
		case WM_KEYUP:
			rep = (lParam >> 0) & 0xFF;
			ext = ((lParam >> 24) & 0x01) == 0x01;
			alt = ((lParam >> 29) & 0x01) == 0x01;
			prev = ((lParam >> 30) & 0x01) == 0x01;
			state = ((lParam >> 31) & 0x01) == 0x01;
			CHECKCB(KeyUp)(window, wParam, rep, ext, alt, prev, state);
		case WM_CLIPBOARDUPDATE: CHECKCB(ClipboardUpdate)(window);
		default: return false;
		}
	}
	void WindowEventListener::SetCloseCallback(CloseCallback cb) {
		Close = cb;
	}
	void WindowEventListener::SetCreateCallback(CreateCallback cb) {
		Create = cb;
	}
	void WindowEventListener::SetDestroyCallback(DestroyCallback cb) {
		Destroy = cb;
	}
	void WindowEventListener::SetEnabledChangedCallback(EnabledChangedCallback cb) {
		EnabledChanged = cb;
	}
	void WindowEventListener::SetSizeMoveStartedCallback(SizeMoveStartedCallback cb) {
		SizeMoveStarted = cb;
	}
	void WindowEventListener::SetSizeMoveEndedCallback(SizeMoveEndedCallback cb) {
		SizeMoveEnded = cb;
	}
	void WindowEventListener::SetMovedCallback(MovedCallback cb) {
		Moved = cb;
	}
	void WindowEventListener::SetMovingCallback(MovingCallback cb) {
		Moving = cb;
	}
	void WindowEventListener::SetPingCallback(PingCallback cb) {
		Ping = cb;
	}
	void WindowEventListener::SetQuitCallback(QuitCallback cb) {
		Quit = cb;
	}
	void WindowEventListener::SetVisibleChangingCallback(VisibleChangingCallback cb) {
		VisibleChanging = cb;
	}
	void WindowEventListener::SetSizeChangedCallback(SizeChangedCallback cb) {
		SizeChanged = cb;
	}
	void WindowEventListener::SetSizeChangingCallback(SizeChangingCallback cb) {
		SizeChanging = cb;
	}
	void WindowEventListener::SetUserChangedCallback(UserChangedCallback cb) {
		UserChanged = cb;
	}
	void WindowEventListener::SetMouseLostCallback(MouseLostCallback cb) {
		MouseLost = cb;
	}
	void WindowEventListener::SetMouseDownCallback(MouseDownCallback cb) {
		MouseDown = cb;
	}
	void WindowEventListener::SetMouseUpCallback(MouseUpCallback cb) {
		MouseUp = cb;
	}
	void WindowEventListener::SetMouseDoubleCallback(MouseDoubleCallback cb) {
		MouseDouble = cb;
	}
	void WindowEventListener::SetMouseCapturedCallback(MouseCapturedCallback cb) {
		MouseCaptured = cb;
	}
	void WindowEventListener::SetMouseLeftCallback(MouseLeftCallback cb) {
		MouseLeft = cb;
	}
	void WindowEventListener::SetMouseHoverCallback(MouseHoverCallback cb) {
		MouseHover = cb;
	}
	void WindowEventListener::SetMouseHWheelCallback(MouseHWheelCallback cb) {
		MouseHWheel = cb;
	}
	void WindowEventListener::SetMouseWheelCallback(MouseWheelCallback cb) {
		MouseWheel = cb;
	}
	void WindowEventListener::SetMouseMoveCallback(MouseMoveCallback cb) {
		MouseMove = cb;
	}
	void WindowEventListener::SetActiveChangedCallback(ActiveChangedCallback cb) {
		ActiveChanged = cb;
	}
	void WindowEventListener::SetAppCommandCallback(AppCommandCallback cb) {
		AppCommandCb = cb;
	}
	void WindowEventListener::SetCharCallback(CharCallback cb) {
		Char = cb;
	}
	void WindowEventListener::SetDeadCharCallback(DeadCharCallback cb) {
		DeadChar = cb;
	}
	void WindowEventListener::SetHotkeyCallback(HotkeyCallback cb) {
		Hotkey = cb;
	}
	void WindowEventListener::SetKeyDownCallback(KeyDownCallback cb) {
		KeyDown = cb;
	}
	void WindowEventListener::SetKeyUpCallback(KeyUpCallback cb) {
		KeyUp = cb;
	}
	void WindowEventListener::SetClipboardUpdateCallback(ClipboardUpdateCallback cb) {
		ClipboardUpdate = cb;
	}

}