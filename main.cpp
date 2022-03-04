#include <stdio.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "mathlib.h"
#endif
#include "log.h"

//#define blog(logLevel, ...) blogInternal(logLevel, __FILE__, __LINE__, __func__, __VA_ARGS__)

int main()
{
    printf("hello world\n");
    int a = 1;
    int b = 2;
    int c = a + b;
#ifdef USE_MYMATH
    c = myadd(a, b);    
#endif    
    printf("%d + %d = %d\n", a, b, c);

	InitSpdLog("D:\\capturesdk.log", BLOG_ALL, BLOG_LEVEL_TRACE);

    //blogInternal(LOG_INFO, __FILE__, __LINE__, __func__, "==========TEST2228888=============");
    blog(LOG_INFO, "==========999999999999==============");

    printf("hello world end\n");

    return 0;
}