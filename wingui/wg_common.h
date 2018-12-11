#pragma once
#include <string>
#include <stdio.h>
#define HASFLAG(v, f) (((v)&(f))==(f))
#define MAKEFLAGS(t) inline t operator|(t a, t b) { return static_cast<t>(static_cast<int>(a) | static_cast<int>(b)); }
namespace wg {
#ifdef UNICODE
	typedef std::wstring _tstring;
#define _tputs(x) wprintf(L"%s\n", x)
#else
	typedef std::string _tstring;
#define _tputs(x) puts(x)
#endif
	void HideConsole();
	void ShowConsole();
}