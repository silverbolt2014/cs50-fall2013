/*
 * Write a program that ask the user for a string then prints outs each 
 * character on a new line
 */

#include <stdio.h>
#include <string.h>
#include "../../cs50lib/cs50.c"

void version1(string input)
{
	int i = 0;
	while(input[i] != '\0')
	{
		printf("%c\n", input[i]);
		i++;
	}
}

void version2(string input)
{
	if (input != NULL)
	{
		int i;
		int n = strlen(input);
		for(i = 0; i < n; i++)
		{
			printf("%c\n", input[i]);
		}
	}

}

int main(void)
{
	printf("Please enter a string that will be spelled out: ");
	string user_string = GetString();
	version2(user_string);


	return 0;
}
