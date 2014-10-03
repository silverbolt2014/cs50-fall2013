/* Write a program that takes a user's full name (two and only two command
 * line arguments).  Next print out a greeting to the user that includes
 * their first name.
 */

#include "../../cs50lib/cs50.c"
#include <stdio.h>

int main(int argc, string argv[])
{
	if (argc != 3)
	{
		printf("Invalid input: Please enter your first and last names.\n");
		return;
	}

	printf("Hello %s %s!\n", argv[1], argv[2]);
}
