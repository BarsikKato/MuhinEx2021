#include <stdio.h>

__declspec(dllexport) int Slozhen(int a, int b);
int Slozhen(int a, int b)
{
    int c = a + b;
    return(c);
}
