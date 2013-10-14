#pragma once
// This file is for extra gloabl defines, think before you add something because you probably don't need to.

#define _FULL_RELEASE

#ifdef _FULL_RELEASE

// Application Information
#define APP_NAME "SquareCubed World Server"
#define APP_VERSION "0.2"
#define APP_AUTHOR "EdgeWorks Games™"
#define STR_SUPPORT "Supported release version!"

#else

// Application Information
#define APP_NAME "SquareCubed World Server"
#define APP_VERSION "0.2-dev"
#define APP_AUTHOR "EdgeWorks Games™"
#define STR_SUPPORT "Unsupported development version!"

#endif