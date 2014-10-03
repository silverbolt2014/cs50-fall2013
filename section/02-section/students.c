/*
 * Write a program that asks the user for five names then randomly chooses and
 * prints out one of the names.
 */

#include <stdio.h>
#include "../../cs50lib/cs50.c"
#include <stdlib.h>
#include <time.h>

#define LENGTH 5

int main(void)
{
	string user_names[LENGTH] = {'\0'};

	int i;
	for (i = 0; i < LENGTH; i++)
	{
		printf("Please enter name %i: ", i);
		user_names[i] = GetString();
	}

	// Print a random name from the array
	// mod 5 can return a value between 0 and 4

	srand( time(NULL) );
	printf("\nA name printed at random: %s\n", user_names[rand() % 5]);	
}
