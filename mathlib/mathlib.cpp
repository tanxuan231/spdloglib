#include "mathlib.h"
#include "log.h"

int myadd(int a, int b)
{
    int c = a + b + 1;
    blog(LOG_INFO, "==== %d + %d = %d", a, b, c);
    return c;
}