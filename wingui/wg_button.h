#pragma once
#ifndef WG_BUTTON_H
#define WG_BUTTON_H
#include <Windows.h>
#include "wg_control.h"
namespace wg::controls {
	using namespace wg::events::button;
	enum ButtonStyle {
		BSBitmap = BS_BITMAP,
		BSBottom = BS_BOTTOM,
		BSCenter = BS_CENTER,
		BSIcon = BS_ICON,
		BSFlat = BS_FLAT,
		BSLeft = BS_LEFT,
		BSMultiline = BS_MULTILINE,
		BSRight = BS_RIGHT,
		BSText = BS_TEXT,
		BSTop = BS_TOP,
		BSVCenter = BS_VCENTER
	};
	MAKEFLAGS(ButtonStyle);
	enum ButtonState {
		BSTChecked = BST_CHECKED,
		BSTFocused = BST_FOCUS,
		BSTMouseOver = BST_HOT,
		BSTIndeterminate = BST_INDETERMINATE,
		BSTPushed = BST_PUSHED,
		BSTNone = BST_UNCHECKED
	};
	MAKEFLAGS(ButtonState);
	typedef unsigned char bool3;
	const bool3 b3checked = 1;
	const bool3 b3indeterminate = 2;
	const bool3 b3unchecked = 3;

	class ButtonEventListener {
	private:
		ButtonMouseEnterCallback MouseEnter;
		ButtonMouseLeaveCallback MouseLeave;
		ButtonClickedCallback Clicked;
		ButtonDoubleClickedCallback DoubleClicked;
		ButtonLostFocusCallback LostFocus;
		ButtonGotFocusCallback GotFocus;
	public:
		ButtonEventListener();
		bool RunMessage(Button*button, UINT uMsg, WPARAM wParam, LPARAM lParam) const;
		void SetMouseEnterCallback(ButtonMouseEnterCallback*cb);
		void SetMouseLeaveCallback(ButtonMouseLeaveCallback*cb);
		void SetClickedCallback(ButtonClickedCallback*cb);
		void SetDoubleClickedCallback(ButtonDoubleClickedCallback*cb);
		void SetLostFocusCallback(ButtonLostFocusCallback*cb);
		void SetGotFocusCallback(ButtonGotFocusCallback*cb);
	};
	class Button : public Control {
	public:
		Button();
		Button(ButtonStyle style);

		void SetShield(bool value);
		void Click() const;
		HBITMAP GetBitmap() const;
		HICON GetIcon() const;
		ButtonState GetState() const;
		void SetEnabled(bool value);
		void SetBitmap(HBITMAP bmp);
		void SetIcon(HICON icon);
		void SetHighlight(bool value);
		void SetEventListener(ButtonEventListener bel);
		ButtonEventListener GetEventListener() const;
	};
	class Button3State : public Button {
	public:
		Button3State();
		Button3State(ButtonStyle style);
		Button3State(bool push);
		Button3State(ButtonStyle style, bool push);

		bool3 GetChecked() const;
		void SetChecked(bool3 value);
		void SetEventListener(ButtonEventListener bel);
		ButtonEventListener GetEventListener() const;
	};
	class CheckBox : public Button {
	public:
		CheckBox();
		CheckBox(ButtonStyle style);
		CheckBox(bool push);
		CheckBox(ButtonStyle style, bool push);

		bool GetChecked() const;
		void SetChecked(bool value);
		void SetEventListener(ButtonEventListener bel);
		ButtonEventListener GetEventListener() const;
	};
	class RadioButton : public Button {
	public:
		RadioButton();
		RadioButton(ButtonStyle style);
		RadioButton(bool push);
		RadioButton(ButtonStyle style, bool push);

		bool GetChecked() const;
		void SetChecked(bool value);
		void SetEventListener(ButtonEventListener bel);
		ButtonEventListener GetEventListener() const;
	};
	class GroupBox : public Control {
	public:
		GroupBox();
	};
}
#endif