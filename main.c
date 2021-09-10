#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

int main ()
{
    static const int line_size = 160;
    
    TEXT inp_txt = {0, NULL};
    
    errno = 0;
    int status = read_file("input.txt", &inp_txt);
    
    if (status == ERROR)
    {
        printf("%s", get_error_codes(errno));
        return 0;
    }
    
    qsort(inp_txt.lines, inp_txt.quan_of_lines, line_size, compare_lines);
    
    errno = 0;
    status = write_file("output.txt", &inp_txt);
    
    if (status == ERROR)
    {
        printf("%s", get_error_codes(errno));
        return 0;
    }
    
    return 0;
}

