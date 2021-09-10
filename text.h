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
int add_line (TEXT *txt, char *line);

/*
    @brief The function to get a pointer to an element of a text by number
    @param *txt is pointer of the text
    @param line_nmb is number of line
    @return Pointer of line in txt with number line_nmb
*/
char *get_line_ptr (TEXT *txt, int line_nmb);

/*
    @brief The function to read all lines from file to text
    @param *file_name is string with name of input file
*/
int read_file (const char *file_name, TEXT *txt);

/*
    @brief The function for line comparison
    @param *str_1, *str_2 is lines to be compared
    @return negative number if the second line is greater than
            0 if the lines are equal
            positive number if the first line is greater than
*/
int compare_lines (const char *str_1, const char *str_2);

/*
    @brief The function to write all lines from text to file
    @param *file_name is string with name of output file
*/
int write_file (const char *file_name, TEXT *txt);

enum FUNCTION_OUTPUTS
{
    SUCCESS = 0,
    ERROR = -1
};

/*
    @brisf The function for converting the error code into a text description
    @perem code is error code from errno.h file
    @return A pointer to a line with an error description
*/
const char *get_error_codes (int code);

#endif

