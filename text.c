#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "text.h"

int input (TEXT *txt, char *file_name)
{
    CHECK_NULLPTR(txt);
    CHECK_NULLPTR(file_name);
	
    
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
    CHECK_NULLPTR(file);
    
    
    struct stat buffer = {};
    fstat (fileno (file), &buffer);
    
    return buffer.st_size;
}

int count_lines (char *str)
{
    CHECK_NULLPTR(str);
    
    
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
    CHECK_NULLPTR(txt);
    
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
    CHECK_NULLPTR(txt);
    CHECK_NULLPTR(file_name);
    
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
    CHECK_NULLPTR(txt);
    CHECK_NULLPTR(file_name);
    
    
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

int compare_lines_original (const void *str_1_par, const void *str_2_par)
{
    assert (str_1_par != NULL);
    assert (str_2_par != NULL);
    
    
    LINE *str_1 = (LINE *) str_1_par;
    LINE *str_2 = (LINE *) str_2_par;
    
    char *count_1 = to_first_liter (str_1->str, FORWARD);
    char *count_2 = to_first_liter (str_2->str, FORWARD);
    
    return strcmp (count_1, count_2);
}

char *to_first_liter (char *str, enum PATH p)
{
    CHECK_NULLPTR(str);
    assert (p != 0);
    
    while ( ( ((*str < 'a') && (*str > 'Z')) || ((*str < 'A')
            &&(*str > '0')) || (*str < '1') ) && (*str != '\0') )
        str += p;
    
    return str;
}

int compare_lines_reverse (const void *str_1_par, const void *str_2_par)
{
    assert (str_1_par != NULL);
    assert (str_2_par != NULL);
    
    LINE *str_1 = (LINE *) str_1_par;
    LINE *str_2 = (LINE *) str_2_par;
    
    
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
    CHECK_NULLPTR(file_name);
    
    FILE *output = fopen (file_name, "a+");
    
    fputs ("\n=================POLTORASHKA=DOES=================\n", output);
    fputs ("===MEOW=MEOW=MEOW=MEOW=MEOW=MEOW=MEOW=MEOW=MEOW===", output);
    fputs ("\n=OWO=OWO=OWO=OWO=OWO=OWO==OWO=OWO=OWO=OWO=OWO=OWO=\n\n", output);
    
    fclose (output);
    
    return SUCCESS;
}

int text_free (TEXT *txt)
{
    CHECK_NULLPTR(txt);
    
    free (txt->lines);
    txt->lines = NULL;
    
    free (txt->text_buffer);
    txt->text_buffer = NULL;
    
    return SUCCESS;
}

static void meow_sort_please (
	    char *base,
        size_t size,
        size_t begin,
        size_t end,
	    int (*cmp)(const void *, const void *)
	)
{
	assert (base != NULL);
	
	
	if (end > begin)
	{
        void *pivot = base + begin;
        int left = begin + size;
        int right = end;
        
        while (left < right)
		{
            if (cmp (base + left, pivot) <= 0)
			{
                left += size;
            }
            
			else
			{
                right -= size;
                SWAP(base + left, base + right, size); 
            }
        }
        left -= size;
        
        SWAP(base + begin, base + left, size);
        meow_sort_please (base, size, begin, left, cmp);
        meow_sort_please (base, size, right, end, cmp);
   }
   
}

void meow_sort (
	    void *base,
	    size_t num,
        size_t size,
	    int (*compare)(const void *, const void *)
	)
{
	meow_sort_please ((char *) base, size, 0, (num - 1) * size, compare);
}

void meowcpy (char *to_mem, char *from_mem, size_t n)
{
	assert (to_mem != NULL);
	assert (from_mem != NULL);
	assert ((n >= 0) && "nullptr error in 'meowcpy'");
	
	
	if ((n == 0) || (to_mem == from_mem))
	{
		return;
	}
	
	
	uint64_t buffer = 0;
	
	while (n >= sizeof (uint64_t))
	{
		buffer = *((uint64_t *) from_mem);
		*((uint64_t *) to_mem) = buffer;
		
		to_mem += sizeof (uint64_t);
		from_mem += sizeof (uint64_t);
		
		n -= sizeof (uint64_t);
	}
	
	
	while (n >= sizeof (uint32_t))
	{
		buffer = *((uint32_t *) from_mem);
		*((uint32_t *) to_mem) = (uint32_t) buffer;
		
		to_mem += sizeof (uint32_t);
		from_mem += sizeof (uint32_t);
		
		n -= sizeof (uint32_t);
	}
	
	
	while (n >= sizeof (uint16_t))
	{
		buffer = *((uint16_t *) from_mem);
		*((uint16_t *) to_mem) = (uint16_t) buffer;
		
		to_mem += sizeof (uint16_t);
		from_mem += sizeof (uint16_t);
		
		n -= sizeof (uint16_t);
	}
	
	
	while (n >= sizeof (uint8_t))
	{
		buffer = *((uint8_t *) from_mem);
		*((uint8_t *) to_mem) = (uint8_t) buffer;
		
		to_mem += sizeof (uint8_t);
		from_mem += sizeof (uint8_t);
		
		n -= sizeof (uint8_t);
	}
}

