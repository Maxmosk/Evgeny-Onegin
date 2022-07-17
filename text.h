/*
    @file This file is designed for inputting, processing, and outputting text
*/

#ifndef TEXT_H
#define TEXT_H


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>


#ifndef NDEBUG
	#include "helper.h"
#endif

/*
    @brief The structure for one line of text
*/
typedef struct LINE
{
    size_t len;
    char *str;
} LINE;

/*
    @brief The structure for text
*/
typedef struct TEXT
{
    size_t file_size;
    size_t quan_lines;
    char *text_buffer;
    LINE *lines;
} TEXT;

/*
    @brief The enum for ways of pathes of search (forvard and reverse)
*/
enum PATH
{
    FORWARD = 1,
    REVERSE = -1
};

/*
    @brief The enum for error codes of functions
*/
enum RETURN_CODES
{
    SUCCESS = -1,
    ERROR = 0
};

/*
    @brief The function to read all lines from file to text
    @param *file_name is string with name of input file
           *txt is the structure from which the read text will be written
    @return Code from RETURN_CODES
    @note Changes the structure by a *txt pointer
*/
int input (TEXT *txt, char *file_name);

/*
    @brief The function to get size of any file
    @param *file is pointer to file, the size of which is required
    @return Size of this file
*/
long get_file_size (FILE *file);

/*
    @brief The function for counting number of lines in string by n-simbols
    @param *str is pointer to processing string
    @return Number of lines in string
*/
size_t count_lines (char *str);

/*
    @brief The function for placement pointers on lines in a string
    @param *txt is pointer to text structure
    @return Code from RETURN_CODES
    @note Changes the structure by a *txt pointer
*/
int set_pointers (TEXT *txt);

/*
    @brief The function for writing text in file by pointers
    @param *txt is text structure for output
           *file_name is string with name of output file
    @return Code from RETURN_CODES
*/
int output_by_ptrs (TEXT *txt, char *file_name);

/*
    @brief The function for writing text in file from text buffer
    @param *txt is text structure for output
           *file_name is string with name of output file
    @return Code from RETURN_CODES
*/
int output_not_sorted (TEXT *txt, char *file_name);

/*
    @brief The function for lines comparation from start to end
    @param *str_1, *str_2 is lines to be compared
    @return negative number if the second line is greater
            0 if the lines are equal
            positive number if the first line is greater
*/
int compare_lines_original (const void *str_1_par, const void *str_2_par);

/*
    @brief The function for finding the first letter of the alphabet
    @param *str is string for search
           p is path of search (forvard or reverse)
    @return pointer on first letter in this string or end of string
*/
char *to_first_liter (char *str, enum PATH p);

/*
    @brief The function for lines comparation from end to start
    @param *str_1, *str_2 is lines to be compared
    @return negative number if the second line is greater than
            0 if the lines are equal
            positive number if the first line is greater than
*/
int compare_lines_reverse (const void *str_1_par, const void *str_2_par);

/*
    @brief The function for writing a text delimiter to a file
    @param *file_name is string with name of output file
    @return Code from RETURN_CODES
    @note This function performs a seance of spiritualism and summons
          the spirit of the POLTORASH, so it must be handled with special care
*/
int write_separation (char *file_name);

/*
    @brief The function for clearing memory, that was used in TEXT structure
    @param *txt is pointer to structure
    @return Code from RETURN_CODES
*/
int text_free (TEXT *txt);

/*
    @brief The function to get string from line in text by number
    @param *txt is pointer to text
    @param line_n number of line
    @return pointer to string or null-pointer in error case
*/
char *get_line (TEXT *txt, size_t line_n);

/*
    @brief The function to get len of line in text by number
    @param *txt is pointer to text
    @param line_n number of line
    @return pointer to len or 0 in error case
*/
size_t get_len (TEXT *txt, size_t line_n);


#endif

