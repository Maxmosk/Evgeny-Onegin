/*
    @mainpage Evgeny Onegin
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"
#include "sort.h"


int main(int argc, char **argv)
{
    assert (argc == 3);
    if (argc != 3)
    {
        printf ("Invalid quantity of command line arguments\n");
        return 0;
    }

    char name_of_inp_file[255] = "";
    
    strncpy (name_of_inp_file, argv[1], 255);
	
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
	strncpy (name_of_out_file, argv[2], 255);
    
    
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
	
    meow_sort (data.lines, data.quan_lines, sizeof (LINE),
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
