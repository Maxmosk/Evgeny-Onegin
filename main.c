#include <stdio.h>
#include <stdlib.h>
#include "text.h"

int main ()
{
	TEXT inp_txt = {0, NULL};
	read_file("input.txt", &inp_txt);
	
	qsort(inp_txt.lines, 17, 80, compare_lines);
	
	printf( "%s", inp_txt.lines  );
	
	return 0;
}

