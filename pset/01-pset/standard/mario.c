/*

Compile using:
gcc -std=c99 mario.c ../../../cs50lib/cs50.c

This is CS50 Pset1 Fall 2013

To print the pyramid:
An equation was determined to figure out how to print each line one by one.

*/

// Uncomment if running on CS50 appliance
// #define RUN_ON_APPLIANCE
#ifdef RUN_ON_APPLIANCE
#include <cs50.h>
#else
#include "../../../cs50lib/cs50.h"
#endif

#include <stdio.h>

int main(void)
{
    // Prompt for and validate user input (valid: 0 to 23)
    int height = -1;
    do
    {
        printf("height: ");
        height = GetInt();
    } while( height < 0 || height > 23);

    // Print the pyramind
    for (int row = 0; row < height; row++)
    {
        // Print Spaces
        int numSpaces = height - 1 - row;
        int numXs = row + 2;
        for (int i = 0; i < numSpaces; i++)
        {
            printf(" ");
        }

        // Print Xs
        for (int i = 0; i < numXs; i++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
