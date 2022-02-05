/*
    @file This file is designed for sorting
*/

#ifndef SORT_H
#define SORT_H


#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>


#define SWAP(_DUNGEON, _MASTER, _FISTING)			\
	char *MEOW_NOT_REPEAT = malloc (_FISTING);		\
	meowcpy (MEOW_NOT_REPEAT, _DUNGEON, _FISTING);	\
	meowcpy (_DUNGEON, _MASTER, _FISTING);			\
	meowcpy (_MASTER, MEOW_NOT_REPEAT, _FISTING);	\
	free (MEOW_NOT_REPEAT);


/*
	@brief The function to copy memory
	@param 	to_mem - pointer on memoty to copy to
			from_mem - pointer on memory with source data
			n - quantity of bytes to copy
	@note May meow during work
*/
void meowcpy (char *to_mem, char *from_mem, size_t n);

/*
	@brief The function for sorting
	@note It is analog fo qsort
*/
void meow_sort (
	    void *base,
	    size_t num,
        size_t size,
	    int (*compare)(const void *, const void *)
	);


#endif

