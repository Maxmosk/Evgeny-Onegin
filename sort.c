#include "sort.h"

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
