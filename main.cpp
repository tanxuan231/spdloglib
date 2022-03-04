#include <stdio.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "mathlib.h"
#endif
#include "log.h"
#include <Windows.h>

//#define blog(logLevel, ...) blogInternal(logLevel, __FILE__, __LINE__, __func__, __VA_ARGS__)

int main()
{
    InitSpdLog("D:\\capturesdk.log", BLOG_ALL, BLOG_LEVEL_TRACE);
    printf("hello world\n");
    int a = 1;
    int b = 2;
    int c = a + b;
#ifdef USE_MYMATH
    c = myadd(a, b);    
#endif    
    printf("%d + %d = %d\n", a, b, c);	

    //blogInternal(LOG_INFO, __FILE__, __LINE__, __func__, "==========TEST2228888=============");
    blog(LOG_ERROR, "==========555433444444==============");

    printf("hello world end\n");
    //Sleep(100);
    DeinitSpdLog();
    return 0;
}