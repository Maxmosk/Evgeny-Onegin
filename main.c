/*
    @mainpage Evgeny Onegin
*/

#include <stdio.h>
#include <stdlib.h>
#include "text.h"

int main(int argc, char **argv)
{
    char name_of_inp_file[255] = "";
    
    if (argc < 1)
    {
		puts ("Input name of file for reading text");
    	scanf ("%s", name_of_inp_file);
	}
	else
	{
		strncpy (&name_of_inp_file, argv[1], 255);
	}
	
    TEXT data = {};
    
    int status = ERROR;
    status = input (&data, name_of_inp_file);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
    
    
    qsort (data.lines, data.quan_lines, sizeof (LINE),
            compare_lines_original);
    
    
    char name_of_out_file[255] = "";
    
    if (argc < 2)
    {
		puts ("Input name of file for writing text");
    	scanf ("%s", name_of_out_file);
	}
	else
	{
		strncpy (&name_of_out_file, argv[2], 255);
	}
    
    
    status = output_by_ptrs (&data, name_of_out_file);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
    
    status = write_separation (name_of_out_file);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
	
    qsort (data.lines, data.quan_lines, sizeof (LINE),
            compare_lines_reverse);
    
    status = output_by_ptrs (&data, name_of_out_file);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
    
    status = write_separation (name_of_out_file);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
    
    status = output_not_sorted (&data, name_of_out_file);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
    
    status = text_free (&data);
    if (status != SUCCESS)
    {
		print_error (status);
		return 0;
	}
    
    return 0;
}
