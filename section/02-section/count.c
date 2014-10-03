/*
 * Write a program that creates an array with the intergers 1 throgh 5 and then
 * prints out each interger on a new line.
 */
#include <stdio.h>

int main(void)
{
	int array[] = {1, 2, 3, 4, 5};

	int i;
	for (i = 0; i < 5; i++)
	{
		printf("%i\n", array[i]);
	}

	return 0;
}
