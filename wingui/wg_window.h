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
		HasBorder = WS_BORDER,
		HasCaption = WS_CAPTION,
		IsDisabled = WS_DISABLED,
		IsDialog = WS_DLGFRAME,
		HasHScroll = WS_HSCROLL,
		IsMinimized = WS_MINIMIZE,
		IsMaximized = WS_MAXIMIZE,
		HasMinimize = WS_MINIMIZEBOX,
		HasMaximize = WS_MAXIMIZEBOX,
		WSDefault = WS_OVERLAPPEDWINDOW,
		Popup = WS_POPUPWINDOW,
		Sizable = WS_SIZEBOX,
		HasWindowMenu = WS_SYSMENU,
		IsVisible = WS_VISIBLE,
		HasVScroll = WS_VSCROLL
	};
	MAKEFLAGS(WindowStyle);
	enum WindowStyleEx {
		WSEXNone = 0,
		WSEXDefault = WS_EX_OVERLAPPEDWINDOW,
		AcceptFiles = WS_EX_ACCEPTFILES,
		SunkenEdge = WS_EX_CLIENTEDGE,
		HasHelp = WS_EX_CONTEXTHELP,
		IsModal = WS_EX_DLGMODALFRAME,
		NoActivate = WS_EX_NOACTIVATE,
		CommandDialog = WS_EX_PALETTEWINDOW,
		ToolWindow = WS_EX_TOOLWINDOW,
		TopMost = WS_EX_TOPMOST,
		RaisedEdge = WS_EX_WINDOWEDGE
	};
	MAKEFLAGS(WindowStyleEx);
	enum WindowClassStyle {
		WCSNone = 0,
		ReceiveDoubleClick = CS_DBLCLKS,
		DropShadow = CS_DROPSHADOW,
		NoClose = CS_NOCLOSE,
		MoveSizeRedraw = CS_VREDRAW | CS_HREDRAW
	};
	MAKEFLAGS(WindowClassStyle);
	class Window;
	class EventListener;
	class Window : public Control {
	private:
		std::vector<Control*> children;
		LPCTSTR class_name;
		EventListener*el;
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
		EventListener*SetEventListener(EventListener*listener);
		EventListener*GetEventListener() const;
	};
	class EventListener {
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
		EventListener();
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