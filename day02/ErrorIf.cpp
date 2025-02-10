#include "ErrorIf.h"

#include <cstdio>
#include <cstdlib>

void ErrorIf(bool b,const char* s)
{
    if(b==true)
        {
            perror(s);
            exit(EXIT_FAILURE);
        }
}