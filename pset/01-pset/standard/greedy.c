/*

Compile using:
gcc -std=c99 greedy.c ../../../cs50lib/cs50.c -lm

This is CS50 Pset1 Fall 2013 - Greedy Problem

*/

#include <stdio.h>
#include <math.h>
#include "../../../cs50lib/cs50.h"

// #define VERSION_1 refers to an implementation using while loops
// #define VERSION_2 refers to an implementation not using while loops
#define VERSION_1

int main(void)
{
	// Prompt user for input and validate input
	float input = -1;

	printf("O hai How much change is owed?\n");
	input = GetFloat();

	while(input <= 0)
	{
		printf("How much change is owed?\n");
		input = GetFloat();
	}

	// Convert from dollars and cents to cents only
	double inputAsCents = round(input * 100);
	
	int cents = (int) inputAsCents;
	int originalAmount = cents;
	//printf("originalAmount in cents = %d\n", originalAmount);

	// Determine minimum number of coins needed
	int numQuarters = 0;
	int numDimes = 0;
	int numNickels = 0;
	int numPennies = 0;

#ifdef VERSION_1
	while (cents >= 25)
	{
		cents = cents - 25;
		numQuarters++;
	}

	while (cents >= 10)
	{
		cents = cents - 10;
		numDimes++;
	}

	while (cents >= 5)
	{
		cents = cents - 5;
		numNickels++;
	}
  
  numPennies = cents;

#endif

#ifdef VERSION_2
  numQuarters = cents / 25;
  cents = cents % 25;
  
  numDimes = cents / 10;
  cents = cents % 10;
  
  numNickels = cents / 5;
  numPennies = cents % 5;
#endif

	// printf("You will need %d quarters, %d dimes, %d nickels, %d pennies\n", numQuarters, numDimes, numNickels, numPennies);
	printf("%d\n", numQuarters + numDimes + numNickels + numPennies);


}
