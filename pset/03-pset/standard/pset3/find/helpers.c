/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Interative Binary Search Algorithm
	int start = 0;
	int end = n - 1;

	//while length of list > 0 
	while (start <= end)
	{
		int middle = (end + start) / 2;
		
		// look at middle of list 
		if (values[middle] == value)
		{
			// if number found, return true
			return true;
		}
		// else if middle higher, search left
		else if ( values[middle] > value )
		{
			end = middle - 1;
		}
		 // else if middle lower, search right
		else if ( values[middle] < value )
		{
			start = middle + 1;
		}
	
	}
    
	return false;
    /*
    // Linear searching algorithm
    if (value < 0 )
    {
        return false;
    }
    else
    {
        int i = 0;
        for (; i < n; i++)
        {
            if (value == values[i])
            {
                return true;
            }
        }
    }
    return false;
    */
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // The code below implements selection sort

    int min_value;
    int min_index;
    bool min_changed;

    for (int i = 0; i < n; i++)
    {
        min_value = values[i];
        min_index = i;
        min_changed = false;

        for (int j = i+1; j < n; j++)
        {
            // printf("i = %i, j = %i\n", i, j);
            if ( min_value > values[j] )
            {
                min_value = values[j];
                min_index = j;
                min_changed = true;
            }
        }
        if ( min_changed )
        {
            int temp = values[i];
            values[i] = min_value;
            values[min_index] = temp;
        }
        
    }

    /*

    printf("\n\nHere is the sorted Array: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%i-", values[i]);
    }
    printf("\n------\n\n");
    */
    
    return;
}
