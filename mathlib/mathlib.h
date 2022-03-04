#pragma once

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif


EXPORT int myadd(int a, int b);