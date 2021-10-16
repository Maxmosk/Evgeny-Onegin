#include "helper.h"

void print_error (int code)
{
    switch (code)
    {
        case EFAULT:
            puts ("Bad adress. A null pointer was passed as a parameter");
            return;
        
        case ENOENT:
            puts ("The file does not exist. The entered file name is incorrect");
            return;
        
        default:
            puts ("Unknown error. Error code: ");
            printf ("%d", code);
            return;
    }
}

