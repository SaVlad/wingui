#include "wg_exceptions.h"
#define CASE_THROW(exc, err) case err: throw new exc()
namespace wg {
	void ThrowWin32Exception(DWORD err) {
		switch (err) {
		case ERROR_INVALID_HANDLE: throw new InvalidHandleException();
		case ERROR_OUTOFMEMORY: throw new OutOfMemoryException();
		default: throw new Win32Exception(err);
		}
	}
	void assert_win32(bool condition) {
		if (!condition) ThrowWin32Exception(GetLastError());
	}
	void assert_win32_maybe() {
		::DWORD __wg__err__ = GetLastError();
		if (__wg__err__) ThrowWin32Exception(__wg__err__);
	}
	Win32Exception::Win32Exception(::DWORD error) : code(error) {
		if (code == 0)
			text = _tstring();
		else {
			LPTSTR buf = nullptr;
			::DWORD size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buf, 0, NULL);
			text = _tstring(buf, size);
			LocalFree(buf);
		}

	}
	::DWORD Win32Exception::GetCode() const {
		return code;
	}
	_tstring Win32Exception::GetDescription() const {
		return text;
	}
}