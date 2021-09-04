#ifndef TEXT_H
#define TEXT_H

struct TEXT
{
	int quan_of_lines;
	char *lines;
};

typedef struct TEXT TEXT;

/*
	@brief The function to add a string to the text
	@detailed This function allocates memory for a new line and adds it to the text
	@param *txt is pointer of the text in which the line is added
	@param *str_2 is string for adding
*/
void add_line (TEXT *txt, char *line);

/*
	@brief The function to get a pointer to an element of a text by number
	@param *txt is pointer of the text
	@param line_nmb is number of line
	@return Pointer of line in txt with number line_nmb
*/
char* get_line_ptr (TEXT *txt, int line_nmb);

/*
	@brief The function to read all lines from file to text
	@param *file_name is string with name of input file
	@return Pointer of text with lines
*/
int read_file (const char *file_name, TEXT *txt);

/*
	@brief The function for line comparison
	@param *str_1, *str_2 is lines to be compared
	@return -1 if the second line is greater than
			0 if the lines are equal
			1 if the first line is greater than
*/
int compare_lines (const char *str_1, const char *str_2);

/*
	@brief The function for simbol comparison
	@param elem_1, *elem_2 is simbols to be compared
	@return -1 if the second simbol is greater than
			0 if the simbol are equal and not equal '\0'
			1 if the first simbol is greater than
			2 if the simbol are equal '\0'
*/
int cmp_simb (char elem_1, char elem_2);

enum cmp_results
{
	FIRST = 1,
	EQUAL_END = 0,
	SECOND = -1,
	EQUAL = 2
};

#endif

