#include "Errorif.h"

void Errorif(bool b,const char* s)
{
    if(b==true)
        {
            perror(s);
            exit(EXIT_FAILURE);
        }
}