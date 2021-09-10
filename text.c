#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

static const int line_size = 160;

void add_line (TEXT *txt, char *line)
{
    assert( (txt != NULL)&&(line != NULL) );
    
    txt->quan_of_lines++;
    
    if (txt->quan_of_lines == 1)
        txt->lines = calloc(line_size, sizeof(char));
    else
        txt->lines = realloc(txt->lines, line_size*txt->quan_of_lines);
    
    strcpy( get_line_ptr(txt, txt->quan_of_lines - 1), line );
}

char *get_line_ptr (TEXT *txt, int line_nmb)
{
    assert(txt != NULL);
    
    return txt->lines + line_size*line_nmb;
}

void read_file (const char *file_name, TEXT *txt)
{
    assert( (txt != NULL)&&(file_name != NULL) );
    
    FILE *inp_file = fopen(file_name, "r");
    char buffer[line_size];
    
    while (fgets(buffer, line_size, inp_file))
    {
        add_line(txt, buffer);
    }
    
    fclose(inp_file);
}

int compare_lines (const char *str_1, const char *str_2)
{
    int i = 0;
    
    while (str_1[i] == str_2[i])
    {
        if (str_1[i] == '\0')
            return 0;
        
        i++;
    }
    
    return str_1[i] - str_2[i];
}

void write_file (const char *file_name, TEXT *txt)
{
    assert( (txt != NULL)&&(file_name != NULL) );
    
    FILE *out_file = fopen(file_name, "w");
    
    for (int i = 0; i < txt->quan_of_lines; i++)
    {
        fputs(get_line_ptr(txt, i), out_file);
    }
    
    fclose(out_file);
}

