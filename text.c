#define NDEBUG
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "text.h"

int input (TEXT *txt, char *file_name)
{
    assert (txt != NULL);
    assert (file_name != NULL);
    if ( (txt == NULL) || (file_name == NULL) )
    {
        return EFAULT;
    }
    
    FILE *bin_input = fopen (file_name, "rb");
    
    if (bin_input == NULL)
    {
        return ENOENT;
    }
    
    txt->file_size = get_file_size (bin_input);
    
    
    if ( (txt->text_buffer = calloc(txt->file_size + 1, sizeof(char))) == NULL )
    {
        return ERROR;
    }
    
    if ( fread (txt->text_buffer, sizeof(char), txt->file_size, bin_input)
                                                    != txt->file_size )
    {
		return ERROR;
	}
    
    txt->text_buffer[txt->file_size] = '\0';
    
    fclose (bin_input);
    
    
    txt->quan_lines = count_lines (txt->text_buffer);
    set_pointers (txt);
    
    return SUCCESS;
}

int get_file_size (FILE *file)
{
    assert (file != NULL);
    if (file == NULL)
    {
        return EFAULT;
    }
    
    struct stat buffer = {};
    fstat (fileno (file), &buffer);
    
    return buffer.st_size;
}

int count_lines (char *str)
{
    assert (str != NULL);
    if (str == NULL)
    {
        return EFAULT;
    }
    
    int quan_of_ilnes = 0;
    int i = 0;
    
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            quan_of_ilnes++;
        
        i++;
    }
    
    return quan_of_ilnes + 1;
}

int set_pointers (TEXT *txt)
{
    assert (txt != NULL);
    if (txt == NULL)
    {
        return EFAULT;
    }
    
    txt->lines = calloc (txt->quan_lines, sizeof (LINE));
    
    char *serch_start  = txt->text_buffer;
    char *finish = NULL;
    
    for (int i = 0; i < txt->quan_lines - 1; ++i)
    {
        char *finish = strchr (serch_start, '\n');

        *finish = '\0';
        
        txt->lines[i].str = serch_start;
        txt->lines[i].len = finish - serch_start;

        serch_start = finish + 1;
    }
    
    txt->lines[txt->quan_lines - 1].str = serch_start;
    txt->lines[txt->quan_lines - 1].len =
                                strlen (txt->lines[txt->quan_lines - 1].str);
    
    
    return SUCCESS;
}

int output_by_ptrs (TEXT *txt, char *file_name)
{
    assert (txt != NULL);
    assert (file_name != NULL);
    if ( (txt == NULL) || (file_name == NULL) )
    {
        return EFAULT;
    }
    
    FILE *output = fopen (file_name, "a+");
    
    for (int i = 0; i < txt->quan_lines; i++)
    {
        fputs (txt->lines[i].str, output);
        fputc ('\n', output);
    }
    
    fclose (output);
    
    return SUCCESS;
}

int output_not_sorted (TEXT *txt, char *file_name)
{
    assert (txt != NULL);
    assert (file_name != NULL);
    if ( (txt == NULL) || (file_name == NULL) )
    {
        return EFAULT;
    }
    
    char *this_str = txt->text_buffer;
    
    FILE *output = fopen (file_name, "a+");
    
    for (int i = 0; i < txt->quan_lines; i++)
    {
        fputs (this_str, output);
        fputc ('\n', output);
        
        this_str = strchr(this_str, '\0') + 1;
    }
    
    fclose (output);
    
    return SUCCESS;
}

int compare_lines_original (LINE *str_1, LINE *str_2)
{
    assert (str_1 != NULL);
    assert (str_2 != NULL);
    
    char *count_1 = to_first_liter (str_1->str, FORWARD);
    char *count_2 = to_first_liter (str_2->str, FORWARD);
    
    return strcmp (count_1, count_2);
}

char *to_first_liter (char *str, enum PATH p)
{
    assert (str != NULL);
    assert (p != 0);
    
    while ( ( ((*str < 'a') && (*str > 'Z')) || ((*str < 'A')
            &&(*str > '0')) || (*str < '1') ) && (*str != '\0') )
        str += p;
    
    return str;
}

int compare_lines_reverse (LINE *str_1, LINE *str_2)
{
    assert (str_1 != NULL);
    assert (str_2 != NULL);
    
    char *count_1 = to_first_liter (str_1->str + str_1->len - 1, REVERSE);
    char *count_2 = to_first_liter (str_2->str + str_2->len - 1, REVERSE);
    
    
    while ( (count_1 > str_1->str)&&(count_2 > str_2->str) )
    {
        if ( (*count_1 == '\0')&&(*count_2 == '\0') )
            return 0;
            
        else if (*count_1 == '\0')
            return -1;
            
        else if (*count_2 == '\0')
            return 1;
        
        
        if (*count_1 == *count_2)
        {
            count_1--;
            count_2--;
        }
        
        else
        {
            return *count_1 - *count_2;
        }
        
    }
    
    return 0;
}

int write_separation (char *file_name)
{
    assert (file_name != NULL);
    if (file_name == NULL)
    {
        return EFAULT;
    }
    
    FILE *output = fopen (file_name, "a+");
    
    fputs ("\n=================POLTORASHKA=DOES=================\n", output);
    fputs ("===MEOW=MEOW=MEOW=MEOW=MEOW=MEOW=MEOW=MEOW=MEOW===", output);
    fputs ("\n=OWO=OWO=OWO=OWO=OWO=OWO==OWO=OWO=OWO=OWO=OWO=OWO=\n\n", output);
    
    fclose (output);
    
    return SUCCESS;
}

int text_free (TEXT *txt)
{
    assert (txt != NULL);
    if (txt == NULL)
    {
        return EFAULT;
    }
    
    free (txt->lines);
    txt->lines = NULL;
    
    free (txt->text_buffer);
    txt->text_buffer = NULL;
    
    return SUCCESS;
}

void print_error (int code)
{
    switch (code)
    {
        case EFAULT:
            puts ("Bad adress. A null pointer was passed as a parameter");
            return;
        
        case ENOENT:
            puts ("The file does not exist. The entered file name is incorrect");
            return;
        
        default:
            puts ("Unknown error. Error code: ");
            printf ("%d", code);
            return;
    }
}

