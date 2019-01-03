#pragma once
#ifndef WG_EVENTS_H
#define WG_EVENTS_H
#include <Windows.h>
#include "wg_common.h"
#include "wg_window.h"
namespace wg::controls { class Window; }
namespace wg::events::window {
	using namespace wg::controls;
	typedef struct tagWindowCreateEventArgs {
		int Width, Height, X, Y;
		_tstring Title;
	} WindowCreateEventArgs;
	enum VisibleChangingStatus {
		VCSManual = 0x0,
		VCSParentMinimizing = SW_PARENTCLOSING,
		VCSParentRestoring = SW_PARENTOPENING,
		VCSCovered = SW_OTHERZOOM,
		VCSUncovered = SW_OTHERUNZOOM
	};
	enum ResizeType {
		RTResized = SIZE_RESTORED,
		RTMinimized = SIZE_MINIMIZED,
		RTMaximized = SIZE_MAXIMIZED,
		RTPopupRestore = SIZE_MAXSHOW,
		RTPopupHide = SIZE_MAXHIDE
	};
	enum ResizingEdge {
		RELeft = WMSZ_LEFT,
		RERight = WMSZ_RIGHT,
		RETop = WMSZ_TOP,
		RETopLeft = WMSZ_TOPLEFT,
		RETopRight = WMSZ_TOPRIGHT,
		REBottom = WMSZ_BOTTOM,
		REBottomLeft = WMSZ_BOTTOMLEFT,
		REBottomRight = WMSZ_BOTTOMRIGHT
	};
	enum MouseButton {
		MBLeft = MK_LBUTTON,
		MBRight = MK_RBUTTON,
		MBMiddle = MK_MBUTTON,
		MBX1 = MK_XBUTTON1,
		MBX2 = MK_XBUTTON2
	};
	enum ActivateType {
		ATDeactivated, ATActivated, ATActivatedByClick
	};
	enum AppCommand {
		ACBassBoost = APPCOMMAND_BASS_BOOST,
		ACBassDown = APPCOMMAND_BASS_DOWN,
		ACBassUp = APPCOMMAND_BASS_UP,
		ACBrowserBackward = APPCOMMAND_BROWSER_BACKWARD,
		ACBrowserFavorites = APPCOMMAND_BROWSER_FAVORITES,
		ACBrowserForward = APPCOMMAND_BROWSER_FORWARD,
		ACBrowserHome = APPCOMMAND_BROWSER_HOME,
		ACBrowserRefresh = APPCOMMAND_BROWSER_REFRESH,
		ACBrowserSearch = APPCOMMAND_BROWSER_SEARCH,
		ACBrowserStop = APPCOMMAND_BROWSER_STOP,
		ACClose = APPCOMMAND_CLOSE,
		ACCopy = APPCOMMAND_COPY,
		ACCorrectionList = APPCOMMAND_CORRECTION_LIST,
		ACCut = APPCOMMAND_CUT,
		ACDictateOrCommandControlToggle = APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE,
		ACFind = APPCOMMAND_FIND,
		ACForwardMail = APPCOMMAND_FORWARD_MAIL,
		ACHelp = APPCOMMAND_HELP,
		ACLaunchApp1 = APPCOMMAND_LAUNCH_APP1,
		ACLaunchApp2 = APPCOMMAND_LAUNCH_APP2,
		ACLaunchMail = APPCOMMAND_LAUNCH_MAIL,
		ACLaunchMediaSelect = APPCOMMAND_LAUNCH_MEDIA_SELECT,
		ACMediaChannelDown = APPCOMMAND_MEDIA_CHANNEL_DOWN,
		ACMediaChannelUp = APPCOMMAND_MEDIA_CHANNEL_UP,
		ACMediaFastForward = APPCOMMAND_MEDIA_FAST_FORWARD,
		ACMediaNextTrack = APPCOMMAND_MEDIA_NEXTTRACK,
		ACMediaPause = APPCOMMAND_MEDIA_PAUSE,
		ACMediaPlay = APPCOMMAND_MEDIA_PLAY,
		ACMediaPlayPause = APPCOMMAND_MEDIA_PLAY_PAUSE,
		ACMediaPreviousTrack = APPCOMMAND_MEDIA_PREVIOUSTRACK,
		ACMediaRecord = APPCOMMAND_MEDIA_RECORD,
		ACMediaRewind = APPCOMMAND_MEDIA_REWIND,
		ACMediaStop = APPCOMMAND_MEDIA_STOP,
		ACMicToggle = APPCOMMAND_MIC_ON_OFF_TOGGLE,
		ACMicVolumeDown = APPCOMMAND_MICROPHONE_VOLUME_DOWN,
		ACMicVolumeMute = APPCOMMAND_MICROPHONE_VOLUME_MUTE,
		ACMicVolumeUp = APPCOMMAND_MICROPHONE_VOLUME_UP,
		ACNew = APPCOMMAND_NEW,
		ACOpen = APPCOMMAND_OPEN,
		ACPaste = APPCOMMAND_PASTE,
		ACPrint = APPCOMMAND_PRINT,
		ACRedo = APPCOMMAND_REDO,
		ACReplyToMail = APPCOMMAND_REPLY_TO_MAIL,
		ACSave = APPCOMMAND_SAVE,
		ACSendMail = APPCOMMAND_SEND_MAIL,
		ACSpellCheck = APPCOMMAND_SPELL_CHECK,
		ACTrebleDown = APPCOMMAND_TREBLE_DOWN,
		ACTrebleUp = APPCOMMAND_TREBLE_UP,
		ACUndo = APPCOMMAND_UNDO,
		ACVolumeDown = APPCOMMAND_VOLUME_DOWN,
		ACVolumeMute = APPCOMMAND_VOLUME_MUTE,
		ACVolumeUp = APPCOMMAND_VOLUME_UP
	};
	enum AppCommandSource {
		ACSKeyboard = FAPPCOMMAND_KEY,
		ACSMouse = FAPPCOMMAND_MOUSE,
		ACSOEM = FAPPCOMMAND_OEM
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
#endif