#pragma once
#ifndef WG_WINDOW_H
#define WG_WINDOW_H
#include <Windows.h>
#include <vector>
#include "wg_control.h"
#include "wg_events.h"
namespace wg::controls {
	using namespace wg::events::window;
	enum WindowStyle {
		WSNone = 0,
		WSDefault = WS_OVERLAPPEDWINDOW,
		WSHasBorder = WS_BORDER,
		WSHasCaption = WS_CAPTION,
		WSIsDisabled = WS_DISABLED,
		WSIsDialog = WS_DLGFRAME,
		WSHasHScroll = WS_HSCROLL,
		WSIsMinimized = WS_MINIMIZE,
		WSIsMaximized = WS_MAXIMIZE,
		WSHasMinimize = WS_MINIMIZEBOX,
		WSHasMaximize = WS_MAXIMIZEBOX,
		WSOverlappedWindow = WS_OVERLAPPEDWINDOW,
		WSPopup = WS_POPUPWINDOW,
		WSSizable = WS_SIZEBOX,
		WSHasWindowMenu = WS_SYSMENU,
		WSIsVisible = WS_VISIBLE,
		WSHasVScroll = WS_VSCROLL
	};
	MAKEFLAGS(WindowStyle);
	enum WindowStyleEx {
		WSEXNone = 0,
		WSEXDefault = WS_EX_OVERLAPPEDWINDOW,
		WSEXOverlappedWindow = WS_EX_OVERLAPPEDWINDOW,
		WSEXAcceptFiles = WS_EX_ACCEPTFILES,
		WSEXSunkenEdge = WS_EX_CLIENTEDGE,
		WSEXHasHelp = WS_EX_CONTEXTHELP,
		WSEXIsModal = WS_EX_DLGMODALFRAME,
		WSEXNoActivate = WS_EX_NOACTIVATE,
		WSEXCommandDialog = WS_EX_PALETTEWINDOW,
		WSEXToolWindow = WS_EX_TOOLWINDOW,
		WSEXTopMost = WS_EX_TOPMOST,
		WSEXRaisedEdge = WS_EX_WINDOWEDGE
	};
	MAKEFLAGS(WindowStyleEx);
	enum WindowClassStyle {
		WCSNone = 0,
		WCSDefault = CS_VREDRAW | CS_HREDRAW,
		WCSReceiveDoubleClick = CS_DBLCLKS,
		WCSDropShadow = CS_DROPSHADOW,
		WCSNoClose = CS_NOCLOSE,
		WCSMoveSizeRedraw = CS_VREDRAW | CS_HREDRAW
	};
	MAKEFLAGS(WindowClassStyle);
	class Window;
	class WindowEventListener;
	class Window : public Control {
	private:
		std::vector<Control*> children;
		LPCTSTR class_name;
		WindowEventListener*el;
	public:
		Window();
		Window(WindowStyle wstyle);
		Window(WindowClassStyle wcstyle);
		Window(WindowStyleEx wexstyle);
		Window(WindowStyle wstyle, WindowStyleEx wexstyle);
		Window(WindowStyle wstyle, WindowClassStyle wcstyle);
		Window(WindowStyleEx wexstyle, WindowClassStyle wcstyle);
		Window(WindowStyle wstyle, WindowStyleEx wexstyle, WindowClassStyle wcstyle);
		~Window();

		void BringToTop();
		void Close();
		SIZE GetClientSize() const;
		void GetClientSize(int*w, int*h) const;
		void SetClientSize(SIZE sz);
		void SetClientSize(int w, int h);
		bool IsMinimized() const;
		void AddChild(Control*ctrl);
		Control*RemoveChild(Control*ctrl);
		Control*RemoveChild(int index);
		int GetChildAmount() const;
		int GetAllChild(Control**childs, int size) const;
		Control*GetChild(int index) const;
		void Hide();
		void Show();
		void Maximize();
		void Minimize();
		void Restore();
		void MessagePump();
		bool OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		WindowEventListener*SetEventListener(WindowEventListener*listener);
		WindowEventListener*GetEventListener() const;
	};
	class WindowEventListener {
	private:
		CloseCallback Close;
		CreateCallback Create;
		DestroyCallback Destroy;
		EnabledChangedCallback EnabledChanged;
		SizeMoveStartedCallback SizeMoveStarted;
		SizeMoveEndedCallback SizeMoveEnded;
		MovedCallback Moved;
		MovingCallback Moving;
		PingCallback Ping;
		QuitCallback Quit;
		VisibleChangingCallback VisibleChanging;
		SizeChangedCallback SizeChanged;
		SizeChangingCallback SizeChanging;
		UserChangedCallback UserChanged;
		MouseLostCallback MouseLost;
		MouseDownCallback MouseDown;
		MouseUpCallback MouseUp;
		MouseDoubleCallback MouseDouble;
		MouseCapturedCallback MouseCaptured;
		MouseLeftCallback MouseLeft;
		MouseHoverCallback MouseHover;
		MouseHWheelCallback MouseHWheel;
		MouseWheelCallback MouseWheel;
		MouseMoveCallback MouseMove;
		ActiveChangedCallback ActiveChanged;
		AppCommandCallback AppCommandCb;
		CharCallback Char;
		DeadCharCallback DeadChar;
		HotkeyCallback Hotkey;
		KeyDownCallback KeyDown;
		KeyUpCallback KeyUp;
		ClipboardUpdateCallback ClipboardUpdate;
	public:
		WindowEventListener();
		bool RunMessage(Window*window, UINT uMsg, WPARAM wParam, LPARAM lParam) const;
		void SetCloseCallback(CloseCallback cb);
		void SetCreateCallback(CreateCallback cb);
		void SetDestroyCallback(DestroyCallback cb);
		void SetEnabledChangedCallback(EnabledChangedCallback cb);
		void SetSizeMoveStartedCallback(SizeMoveStartedCallback cb);
		void SetSizeMoveEndedCallback(SizeMoveEndedCallback cb);
		void SetMovedCallback(MovedCallback cb);
		void SetMovingCallback(MovingCallback cb);
		void SetPingCallback(PingCallback cb);
		void SetQuitCallback(QuitCallback cb);
		void SetVisibleChangingCallback(VisibleChangingCallback cb);
		void SetSizeChangedCallback(SizeChangedCallback cb);
		void SetSizeChangingCallback(SizeChangingCallback cb);
		void SetUserChangedCallback(UserChangedCallback cb);
		void SetMouseLostCallback(MouseLostCallback cb);
		void SetMouseDownCallback(MouseDownCallback cb);
		void SetMouseUpCallback(MouseUpCallback cb);
		void SetMouseDoubleCallback(MouseDoubleCallback cb);
		void SetMouseCapturedCallback(MouseCapturedCallback cb);
		void SetMouseLeftCallback(MouseLeftCallback cb);
		void SetMouseHoverCallback(MouseHoverCallback cb);
		void SetMouseHWheelCallback(MouseHWheelCallback cb);
		void SetMouseWheelCallback(MouseWheelCallback cb);
		void SetMouseMoveCallback(MouseMoveCallback cb);
		void SetActiveChangedCallback(ActiveChangedCallback cb);
		void SetAppCommandCallback(AppCommandCallback cb);
		void SetCharCallback(CharCallback cb);
		void SetDeadCharCallback(DeadCharCallback cb);
		void SetHotkeyCallback(HotkeyCallback cb);
		void SetKeyDownCallback(KeyDownCallback cb);
		void SetKeyUpCallback(KeyUpCallback cb);
		void SetClipboardUpdateCallback(ClipboardUpdateCallback cb);
	};
}
#endif