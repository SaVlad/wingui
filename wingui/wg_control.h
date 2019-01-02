#pragma once
#ifndef WG_CONTROL_H
#define WG_CONTROL_H
#include "wg_common.h"
namespace wg::controls {
	class Control {
	protected:
		HWND handle;
		Control();
		void check_handle() const;
	public:
		void SetPosition(int x, int y);
		void SetPosition(POINT pt);
		POINT GetPosition() const;
		void GetPosition(int*x, int*y) const;
		void SetSize(int w, int h);
		void SetSize(SIZE sz);
		SIZE GetSize() const;
		void GetSize(int*w, int*h) const;
		void SetText(LPCTSTR text);
		void SetText(_tstring text);
		int GetTextLength() const;
		int GetText(LPTSTR buffer, int length) const;
		_tstring GetText() const;
		LRESULT Message(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void MessageImmediate(UINT uMsg, WPARAM wParam, LPARAM lParam);
		HWND GetHandle() const;
	};
}
#endif