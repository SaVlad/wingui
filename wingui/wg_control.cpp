#include "wg_exceptions.h"
#include "wg_control.h"
namespace wg::controls {
	using namespace wg::exceptions;
	void Control::check_handle() const {
		if (handle == nullptr) throw new InvalidHandleException();
	}
	Control::Control() {
		handle = nullptr;
	}
	void Control::SetPosition(int x, int y) {
		check_handle();
		assert_win32(SetWindowPos(handle, NULL, x, y, NULL, NULL, SWP_NOZORDER | SWP_NOSIZE));
	}
	void Control::SetPosition(POINT pt) {
		SetPosition(pt.x, pt.y);
	}
	POINT Control::GetPosition() const {
		POINT pt;
		GetPosition((int*)&pt.x, (int*)&pt.y);
		return pt;
	}
	void Control::GetPosition(int*x, int*y) const {
		check_handle();
		RECT r;
		assert_win32(GetWindowRect(handle, &r));
		*x = (int)r.left;
		*y = (int)r.top;
	}
	void Control::SetSize(int w, int h) {
		check_handle();
		assert_win32(SetWindowPos(handle, NULL, NULL, NULL, w, h, SWP_NOZORDER | SWP_NOMOVE));
	}
	void Control::SetSize(SIZE sz) {
		SetSize(sz.cx, sz.cy);
	}
	SIZE Control::GetSize() const {
		SIZE sz;
		GetSize((int*)&sz.cx, (int*)&sz.cy);
		return sz;
	}
	void Control::GetSize(int*w, int*h) const {
		check_handle();
		RECT r;
		assert_win32(GetWindowRect(handle, &r));
		*w = (int)(r.right - r.left);
		*h = (int)(r.bottom - r.top);
	}
	void Control::SetText(LPCTSTR text) {
		check_handle();
		assert_win32(SetWindowText(handle, text));
	}
	void Control::SetText(_tstring text) {
		SetText(text.c_str());
	}
	int Control::GetTextLength() const {
		check_handle();
		int r = GetWindowTextLength(handle);
		assert_win32_maybe();
		return r;
	}
	int Control::GetText(LPTSTR buffer, int length) const {
		check_handle();
		int r = GetWindowText(handle, buffer, length);
		assert_win32_maybe();
		return r;
	}
	_tstring Control::GetText() const {
		int len = GetTextLength();
		LPTSTR buffer = new TCHAR[len + 1];
		GetText(buffer, len + 1);
		_tstring ret(buffer);
		delete[]buffer;
		return ret;
	}
	LRESULT Control::Message(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		check_handle();
		return SendMessage(handle, uMsg, wParam, lParam);
	}
	void Control::MessageImmediate(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		check_handle();
		assert_win32(PostMessage(handle, uMsg, wParam, lParam));
	}
	HWND Control::GetHandle() const {
		return handle;
	}
}