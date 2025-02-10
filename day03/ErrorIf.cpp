#include "ErrorIf.h"

void ErrorIf(bool b,const char* s)
{
    if(b==true)
        {
            perror(s);
            exit(EXIT_FAILURE);
        }
}