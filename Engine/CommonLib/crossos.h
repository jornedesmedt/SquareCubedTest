#pragma once

// This document has been added for wrappers of OS functions,
// the following functions have to be added to a new platform
// if you are adding one to this file:
// - void ErrorDialogBox(const char* title, const char* message)

#ifdef _WIN32
#include <Windows.h>

void ErrorMessageBox(const char* title, const char* message) {
	MessageBox(NULL, message, title, MB_OK | MB_ICONERROR);
}
#else
#error Unsupported platform, please add platform dependent wrappers for your platform.
#endif