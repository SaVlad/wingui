#include <Windows.h>
#include "wg_common.h"
namespace wg {
	void HideConsole() {
		HWND hWnd = GetConsoleWindow();
		if (hWnd)
			ShowWindow(hWnd, SW_HIDE);
	}
	void ShowConsole() {
		HWND hWnd = GetConsoleWindow();
		if (hWnd)
			ShowWindow(hWnd, SW_SHOW);
	}
}