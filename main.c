/*
    @mainpage Evgeny Onegin
*/

#include <stdio.h>
#include <stdlib.h>
#include "text.h"

int main()
{
    char name_of_inp_file[255] = "";
    scanf ("%s", name_of_inp_file);
    
    TEXT data = {};
    
    int status = ERROR;
    errno = 0;
    status = input (&data, name_of_inp_file);
    if (status == ERROR)
    { print_error (errno); return 0; }
    
    qsort (data.lines, data.quan_lines, sizeof (LINE),
            compare_lines_original);
    
    char name_of_out_file[255] = "";
    scanf ("%s", name_of_out_file);
    
    errno = 0;
    output_by_ptrs (&data, name_of_out_file);
    if (status == ERROR)
    { print_error (errno); return 0; }
    
    errno = 0;
    write_separation (name_of_out_file);
    
    qsort (data.lines, data.quan_lines, sizeof (LINE),
            compare_lines_reverse);
    
    errno = 0;
    output_by_ptrs (&data, name_of_out_file);
    if (status == ERROR)
    { print_error (errno); return 0; }
    
    errno = 0;
    write_separation (name_of_out_file);
    if (status == ERROR)
    { print_error (errno); return 0; }
    
    errno = 0;
    output_not_sorted (&data, name_of_out_file);
    if (status == ERROR)
    { print_error (errno); return 0; }
    
    errno = 0;
    text_free (&data);
    if (status == ERROR)
    { print_error (errno); return 0; }
    
    return 0;
}
