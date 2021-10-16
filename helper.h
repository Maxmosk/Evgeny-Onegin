#ifndef HELPER_H
#define HELPER_H

#include <errno.h>
#include <stdlib.h>

#include "text.h"

/*
	@brief The macro for cheking function result for error
	@note Must be called ONLY from function 'main'
*/
#define CHECK_ERROR(status)		\
	if (status != SUCCESS)		\
    {							\
        print_error (status);	\
        return 0;				\
    }

/*
	@brief The macro for cheking pointer on nullptr
	@note Must be called ONLY from not function 'main'
*/
#define CHECK_NULLPTR(ptr)		\
	assert (ptr != NULL);		\
    if (ptr == NULL)			\
    {							\
        return EFAULT;			\
    }


/*
    @brief The function for output of the errno.h error code description
    @param code is code of error from errno.h
*/
void print_error (int code);

#endif

