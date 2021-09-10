#define NDEBUG
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

static const int line_size = 160;

int add_line (TEXT *txt, char *line)
{
    // pointer checking
    assert( (txt != NULL)&&(line != NULL) );
    if ( (txt == NULL)||(line == NULL) )
    {
        errno = EFAULT;
        return ERROR;
    }
    
    txt->quan_of_lines++;
    
    if (txt->quan_of_lines == 1)
        txt->lines = calloc(line_size, sizeof(char));
    else
        txt->lines = realloc(txt->lines, line_size*txt->quan_of_lines);
    
    strcpy( get_line_ptr(txt, txt->quan_of_lines - 1), line );
    
    return SUCCESS;
}

char *get_line_ptr (TEXT *txt, int line_nmb)
{
    // pointer checking
    assert(txt != NULL);
    
    return txt->lines + line_size*line_nmb;
}

int read_file (const char *file_name, TEXT *txt)
{
    // pointer checking
    assert( (txt != NULL)&&(file_name != NULL) );
    if ( (txt == NULL)||(file_name == NULL) )
    {
        errno = EFAULT;
        return ERROR;
    }
    
    FILE *inp_file = fopen(file_name, "r");
    
    // checking existing of input file
    if (inp_file == NULL)
    {
        errno = ENOENT;
        return ERROR;
    }
    
    char buffer[line_size];
    int status = 0;
    
    while (fgets(buffer, line_size, inp_file))
    {
        status = add_line(txt, buffer);
        
        if (status == ERROR)
        {
        	return ERROR;
		}
    }
    
    fclose(inp_file);
    
    return SUCCESS;
}

int compare_lines (const char *str_1, const char *str_2)
{
    // pointer checking
    assert( (str_1 != NULL)&&(str_2 != NULL) );
    
    int i = 0;
    
    while (str_1[i] == str_2[i])
    {
        if (str_1[i] == '\0')
            return 0;
        
        i++;
    }
    
    return str_1[i] - str_2[i];
}

int write_file (const char *file_name, TEXT *txt)
{
    // pointer checking
    assert( (txt != NULL)&&(file_name != NULL) );
    if ( (txt == NULL)||(file_name == NULL) )
    {
        errno = EFAULT;
        return ERROR;
    }
    
    FILE *out_file = NULL;
    
    // checking existing of output file
    if ( (out_file = fopen(file_name, "r")) == NULL )
    {
        fclose(out_file);
    }
    else
    {
        fclose(out_file);
        
        errno = EEXIST;
        return ERROR;
    }
    
    out_file = fopen(file_name, "w");
    
    for (int i = 0; i < txt->quan_of_lines; i++)
    {
        fputs(get_line_ptr(txt, i), out_file);
    }
    
    fclose(out_file);
}

const char *get_error_codes (int code)
{
    switch (code)
    {
        case EEXIST:
            return "The file named output.txt already exists";
            
        case EFAULT:
            return "An invalid pointer was passed";
        
        case ENOENT:
            return "The file named input.txt does not exist";
        
        default:
            return "Unknown error";
    }
}

