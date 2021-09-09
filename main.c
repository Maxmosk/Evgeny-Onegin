#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"

int main ()
{
	static const int line_size = 160;
	
	TEXT inp_txt = {0, NULL};
	read_file("input.txt", &inp_txt);
	
	qsort(inp_txt.lines, inp_txt.quan_of_lines, line_size, compare_lines);
	
	write_file("output.txt", &inp_txt);
	
	return 0;
}

