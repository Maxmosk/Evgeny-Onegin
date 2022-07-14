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
                meowswap (base + left, base + right, size); 
            }
        }
        left -= size;

        
        meowswap (base + begin, base + left, size);

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

void meowswap (char *mem_1, char *mem_2, size_t n)
{
	assert (mem_1 != NULL);
	assert (mem_2 != NULL);
	
	
	if ((n == 0) || (mem_1 == mem_2))
	{
		return;
	}
	
	
	uint64_t buffer = 0;
	
	while (n >= sizeof (uint64_t))
	{
		buffer = *((uint64_t *) mem_1);
		*((uint64_t *) mem_1) = *((uint64_t *) mem_2);
		*((uint64_t *) mem_2) = buffer;
		

		mem_2 += sizeof (uint64_t);
		mem_1 += sizeof (uint64_t);
		
		n -= sizeof (uint64_t);
	}

    while (n >= sizeof (uint32_t))
	{
		buffer = *((uint32_t *) mem_1);
		*((uint32_t *) mem_1) = *((uint32_t *) mem_2);
		*((uint32_t *) mem_2) = buffer;
		

		mem_2 += sizeof (uint32_t);
		mem_1 += sizeof (uint32_t);
		
		n -= sizeof (uint32_t);
	}

    while (n >= sizeof (uint16_t))
	{
		buffer = *((uint16_t *) mem_1);
		*((uint16_t *) mem_1) = *((uint16_t *) mem_2);
		*((uint16_t *) mem_2) = buffer;
		

		mem_2 += sizeof (uint16_t);
		mem_1 += sizeof (uint16_t);
		
		n -= sizeof (uint16_t);
	}

    while (n >= sizeof (uint8_t))
	{
		buffer = *((uint8_t *) mem_1);
		*((uint8_t *) mem_1) = *((uint8_t *) mem_2);
		*((uint8_t *) mem_2) = buffer;
		

		mem_2 += sizeof (uint8_t);
		mem_1 += sizeof (uint8_t);
		
		n -= sizeof (uint8_t);
	}

}
