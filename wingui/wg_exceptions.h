#pragma once
#ifndef WG_EXCEPTIONS_H
#define WG_EXCEPTIONS_H
#include <Windows.h>
#include <exception>
#include "wg_common.h"
#define WIN32_EXCEPTION_CLASS(x,exc) class x:public Win32Exception{public:x():Win32Exception(exc){}};
namespace wg {
	void ThrowWin32Exception(DWORD err);
	void assert_win32(bool condition);
	void assert_win32_maybe();
	class Win32Exception : public std::exception {
	private:
		::DWORD code;
		_tstring text;
	public:
		Win32Exception(::DWORD error);
		::DWORD GetCode() const;
		_tstring GetDescription() const;
	};
	WIN32_EXCEPTION_CLASS(InvalidHandleException, ERROR_INVALID_WINDOW_HANDLE);
	WIN32_EXCEPTION_CLASS(OutOfMemoryException, ERROR_OUTOFMEMORY);
}
#undef WIN32_EXCEPTION_CLASS
#endif