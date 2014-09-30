/*

Compile using:
gcc -std=c99 mario.c ../../cs50lib/cs50.c

This is CS50 Pset1 Fall 2013

To print the pyramid:
An equation was determined to figure out how to print each line by one.

*/

#include <stdio.h>
#include "../../cs50lib/cs50.h"

int main(void)
{
	// Prompt and valid user input (0 to 23)
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
			printf("X");
		}
		printf("\n");
	}
}
