/*
    @file This file is designed for sorting
*/

#ifndef SORT_H
#define SORT_H


#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>


/*
	@brief The function to swap memory
	@param mem_1, mem_2 - pointer on memoty to copy to
			n - quantity of bytes to swap
	@note May meow during work
*/
void meowswap (uint8_t *mem_1, uint8_t *mem_2, size_t n);

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

