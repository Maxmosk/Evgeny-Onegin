#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

const int line_size = 80;

void add_line (TEXT *txt, char *line)
{
	assert( (txt != NULL)&&(line != NULL) );
	
	txt->quan_of_lines++;
	
	if (txt->quan_of_lines == 1)
		txt->lines = malloc(line_size);
	else
		realloc(txt->lines, line_size*txt->quan_of_lines);
	
	strcpy( get_line_ptr(txt, txt->quan_of_lines - 1), line );
}

char* get_line_ptr (TEXT *txt, int line_nmb)
{
	assert( (txt != NULL) );
	
	return txt->lines + line_size*line_nmb;
}

int read_file (const char *file_name, TEXT *txt)
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
	assert( (str_1 != NULL)&&(str_2 != NULL) );
	
	printf("%s --- %s\n", str_1, str_2);
	
	int i = 0;
	int cmp_res = 0;
	
	do
	{
		cmp_res = cmp_simb(str_1[i], str_2[i]);
		i++;
	}
	while ( (cmp_res != EQUAL_END)&&(i < line_size) );
	
	return cmp_res;
}

int cmp_simb (char elem_1, char elem_2)
{
	
	if ( (elem_1 < elem_2) )
		return FIRST;
	
	else if ( (elem_1 > elem_2) )
		return SECOND;
	
	else if ( (elem_1 == '\0')&&(elem_2 == '\0') )
		return EQUAL_END;
	
	else
		return EQUAL;
}

