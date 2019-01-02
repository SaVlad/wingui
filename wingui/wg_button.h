#pragma once
#ifndef WG_BUTTON_H
#define WG_BUTTON_H
#include <Windows.h>
#include "wg_control.h"
namespace wg::controls {
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
	class ButtonEventListener {
	private:

	public:
		ButtonEventListener();
		bool RunMessage(Window*window, UINT uMsg, WPARAM wParam, LPARAM lParam) const;
	};
	class Button : public Control {
	public:
		Button();
		Button(ButtonStyle style);
	};
	class Button3State : public Control {
	public:
		Button3State();
		Button3State(ButtonStyle style);
		Button3State(bool push);
		Button3State(ButtonStyle style, bool push);
	};
	class CheckBox : public Control {
	public:
		CheckBox();
		CheckBox(ButtonStyle style);
		CheckBox(bool push);
		CheckBox(ButtonStyle style, bool push);
	};
	class RadioButton : public Control {
	public:
		RadioButton();
		RadioButton(ButtonStyle style);
		RadioButton(bool push);
		RadioButton(ButtonStyle style, bool push);
	};
	class GroupBox : public Control {
	public:
		GroupBox();
	};
}
#endif