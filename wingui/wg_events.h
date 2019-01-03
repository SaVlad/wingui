#pragma once
#ifndef WG_EVENTS_H
#define WG_EVENTS_H
#include <Windows.h>
#include "wg_common.h"
#include "wg_window.h"
#include "wg_button.h"
namespace wg::controls {
	class Window;
	class Button;
}
namespace wg::events::window {
	using namespace wg::controls;
	typedef struct tagWindowCreateEventArgs {
		int Width, Height, X, Y;
		_tstring Title;
	} WindowCreateEventArgs;
	enum VisibleChangingStatus {
		Manual = 0x0,
		ParentMinimizing = SW_PARENTCLOSING,
		parentRestoring = SW_PARENTOPENING,
		Covered = SW_OTHERZOOM,
		Uncovered = SW_OTHERUNZOOM
	};
	enum ResizeType {
		Resized = SIZE_RESTORED,
		Minimized = SIZE_MINIMIZED,
		Maximized = SIZE_MAXIMIZED,
		PopupRestore = SIZE_MAXSHOW,
		PopupHide = SIZE_MAXHIDE
	};
	enum ResizingEdge {
		Left = WMSZ_LEFT,
		Right = WMSZ_RIGHT,
		Top = WMSZ_TOP,
		TopLeft = WMSZ_TOPLEFT,
		TopRight = WMSZ_TOPRIGHT,
		Bottom = WMSZ_BOTTOM,
		BottomLeft = WMSZ_BOTTOMLEFT,
		BottomRight = WMSZ_BOTTOMRIGHT
	};
	enum MouseButton {
		LeftButton = MK_LBUTTON,
		RightButton = MK_RBUTTON,
		MiddleButton = MK_MBUTTON,
		XButton1 = MK_XBUTTON1,
		XButton2 = MK_XBUTTON2
	};
	enum ActivateType {
		Deactivated, Activated, ActivatedByClick
	};
	enum AppCommand {
		BassBoost = APPCOMMAND_BASS_BOOST,
		BassDown = APPCOMMAND_BASS_DOWN,
		BassUp = APPCOMMAND_BASS_UP,
		BrowserBackward = APPCOMMAND_BROWSER_BACKWARD,
		BrowserFavorites = APPCOMMAND_BROWSER_FAVORITES,
		BrowserForward = APPCOMMAND_BROWSER_FORWARD,
		BrowserHome = APPCOMMAND_BROWSER_HOME,
		BrowserRefresh = APPCOMMAND_BROWSER_REFRESH,
		BrowserSearch = APPCOMMAND_BROWSER_SEARCH,
		BrowserStop = APPCOMMAND_BROWSER_STOP,
		Close = APPCOMMAND_CLOSE,
		Copy = APPCOMMAND_COPY,
		CorrectionList = APPCOMMAND_CORRECTION_LIST,
		Cut = APPCOMMAND_CUT,
		DictateOrCommandControlToggle = APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE,
		Find = APPCOMMAND_FIND,
		ForwardMail = APPCOMMAND_FORWARD_MAIL,
		Help = APPCOMMAND_HELP,
		LaunchApp1 = APPCOMMAND_LAUNCH_APP1,
		LaunchApp2 = APPCOMMAND_LAUNCH_APP2,
		LaunchMail = APPCOMMAND_LAUNCH_MAIL,
		LaunchMediaSelect = APPCOMMAND_LAUNCH_MEDIA_SELECT,
		MediaChannelDown = APPCOMMAND_MEDIA_CHANNEL_DOWN,
		MediaChannelUp = APPCOMMAND_MEDIA_CHANNEL_UP,
		MediaFastForward = APPCOMMAND_MEDIA_FAST_FORWARD,
		MediaNextTrack = APPCOMMAND_MEDIA_NEXTTRACK,
		MediaPause = APPCOMMAND_MEDIA_PAUSE,
		MediaPlay = APPCOMMAND_MEDIA_PLAY,
		MediaPlayPause = APPCOMMAND_MEDIA_PLAY_PAUSE,
		MediaPreviousTrack = APPCOMMAND_MEDIA_PREVIOUSTRACK,
		MediaRecord = APPCOMMAND_MEDIA_RECORD,
		MediaRewind = APPCOMMAND_MEDIA_REWIND,
		MediaStop = APPCOMMAND_MEDIA_STOP,
		MicToggle = APPCOMMAND_MIC_ON_OFF_TOGGLE,
		MicVolumeDown = APPCOMMAND_MICROPHONE_VOLUME_DOWN,
		MicVolumeMute = APPCOMMAND_MICROPHONE_VOLUME_MUTE,
		MicVolumeUp = APPCOMMAND_MICROPHONE_VOLUME_UP,
		New = APPCOMMAND_NEW,
		Open = APPCOMMAND_OPEN,
		Paste = APPCOMMAND_PASTE,
		Print = APPCOMMAND_PRINT,
		Redo = APPCOMMAND_REDO,
		ReplyToMail = APPCOMMAND_REPLY_TO_MAIL,
		Save = APPCOMMAND_SAVE,
		SendMail = APPCOMMAND_SEND_MAIL,
		SpellCheck = APPCOMMAND_SPELL_CHECK,
		TrebleDown = APPCOMMAND_TREBLE_DOWN,
		TrebleUp = APPCOMMAND_TREBLE_UP,
		Undo = APPCOMMAND_UNDO,
		VolumeDown = APPCOMMAND_VOLUME_DOWN,
		VolumeMute = APPCOMMAND_VOLUME_MUTE,
		VolumeUp = APPCOMMAND_VOLUME_UP
	};
	enum AppCommandSource {
		Keyboard = FAPPCOMMAND_KEY,
		Mouse = FAPPCOMMAND_MOUSE,
		OEM = FAPPCOMMAND_OEM
	};

	typedef bool(CALLBACK*CloseCallback)(Window*window); // WM_CLOSE
	typedef bool(CALLBACK*CreateCallback)(Window*window, WindowCreateEventArgs args); // WM_CREATE
	typedef bool(CALLBACK*DestroyCallback)(Window*window); // WM_DESTROY
	typedef bool(CALLBACK*EnabledChangedCallback)(Window*window, bool isEnabled); // WM_ENABLE
	typedef bool(CALLBACK*SizeMoveStartedCallback)(Window*window); // WM_ENTERSIZEMOVE
	typedef bool(CALLBACK*SizeMoveEndedCallback)(Window*window); // WM_EXITSIZEMOVE
	typedef bool(CALLBACK*MovedCallback)(Window*window, WORD x, WORD y); // WM_MOVE
	typedef bool(CALLBACK*MovingCallback)(Window*window, LONG*x, LONG*y); // WM_MOVING
	typedef bool(CALLBACK*PingCallback)(Window*window); // WM_NULL
	typedef bool(CALLBACK*QuitCallback)(Window*window, DWORD code); // WM_QUIT
	typedef bool(CALLBACK*VisibleChangingCallback)(Window*window, bool shown, VisibleChangingStatus status); // WM_SHOWWINDOW
	typedef bool(CALLBACK*SizeChangedCallback)(Window*window, ResizeType type, WORD w, WORD h); // WM_SIZE
	typedef bool(CALLBACK*SizeChangingCallback)(Window*window, ResizingEdge edge, LONG*x, LONG*y, LONG*w, LONG*h); // WM_SIZING
	typedef bool(CALLBACK*UserChangedCallback)(Window*window); // WM_USERCHANGED

	typedef bool(CALLBACK*MouseLostCallback)(Window*window); // WM_CAPTURECHANGED
	typedef bool(CALLBACK*MouseDownCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl); // WM_LBUTTONDOWN, WM_MBUTTONDOWN, WM_RBUTTONDOWN, WM_XBUTTONDOWN
	typedef bool(CALLBACK*MouseUpCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl); // WM_LBUTTONUP, WM_MBUTTONUP, WM_RBUTTONUP, WM_XBUTTONUP
	typedef bool(CALLBACK*MouseDoubleCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl); // WM_LBUTTONDBLCLK, WM_MBUTTONDBLCLK, WM_RBUTTONDBLCLK, WM_XBUTTONDBLCLK
	typedef bool(CALLBACK*MouseCapturedCallback)(Window*window); // WM_MOUSEACTIVATE
	typedef bool(CALLBACK*MouseLeftCallback)(Window*window); // WM_MOUSELEAVE
	typedef bool(CALLBACK*MouseHoverCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl); // WM_MOUSEHOVER
	typedef bool(CALLBACK*MouseHWheelCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl, WORD delta); // WM_MOUSEHWHEEL
	typedef bool(CALLBACK*MouseWheelCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl, WORD delta); // WM_MOUSEWHEEL
	typedef bool(CALLBACK*MouseMoveCallback)(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl); // WM_MOUSEMOVE

	typedef bool(CALLBACK*ActiveChangedCallback)(Window*window, ActivateType type); // WM_ACTIVATE
	typedef bool(CALLBACK*AppCommandCallback)(Window*window, AppCommand cmd, AppCommandSource source, MouseButton buttons, bool shift, bool ctrl); // WM_APPCOMMAND
	typedef bool(CALLBACK*CharCallback)(Window*window, DWORD key, int repeat, bool extended, bool alt, bool previous, bool state); // WM_CHAR
	typedef bool(CALLBACK*DeadCharCallback)(Window*window, DWORD key, int repeat, bool extended, bool alt, bool previous, bool state); // WM_DEADCHAR
	typedef bool(CALLBACK*HotkeyCallback)(Window*window, int id); // WM_HOTKEY
	typedef bool(CALLBACK*KeyDownCallback)(Window*window, DWORD key, int repeat, bool extended, bool alt, bool previous, bool state); // WM_KEYDOWN
	typedef bool(CALLBACK*KeyUpCallback)(Window*window, DWORD key, int repeat, bool extended, bool alt, bool previous, bool state); // WM_KEYUP

	typedef bool(CALLBACK*ClipboardUpdateCallback)(Window*window); // WM_CLIPBOARDUPDATE
}
namespace wg::events::button {
	using namespace wg::controls;

	typedef bool(CALLBACK*ButtonMouseEnterCallback)(Button*button); // BCN_HOTITEMCHANGE
	typedef bool(CALLBACK*ButtonMouseLeaveCallback)(Button*button); // BCN_HOTITEMCHANGE
	typedef bool(CALLBACK*ButtonClickedCallback)(Button*button); // BN_CLICKED
	typedef bool(CALLBACK*ButtonDoubleClickedCallback)(Button*button); // BN_DBLCLK
	typedef bool(CALLBACK*ButtonLostFocusCallback)(Button*button); // BN_KILLFOCUS
	typedef bool(CALLBACK*ButtonGotFocusCallback)(Button*button); // BN_SETFOCUS
}
#endif