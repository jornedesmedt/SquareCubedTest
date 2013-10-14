#pragma once

// This file contains a series of solutions to allow cross-compiler compiling.


#ifdef __GNUC__
#define __deprec(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define __deprec(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement __deprec for this compiler")
#define __deprec(func) func
#endif