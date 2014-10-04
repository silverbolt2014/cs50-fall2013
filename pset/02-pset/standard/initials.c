/*
 * Next, write, in a file called initials.c, a program that prompts a user for
 * their name (using GetString to obtain their name as a string) and then
 * outputs their initials in uppercase with no spaces or periods, followed by
 * a newline (\n) and nothing more. You may assume that the user’s input will
 * contain only letters (uppercase and/or lowercase) plus single spaces between
 * words. Folks like Joseph Gordon-Levitt, Conan O’Brien, and R.J. Aquino
 * won’t be using your program.
 */

#include <stdio.h>
#include "../../../cs50lib/cs50.c"

#define SPACE ' '

int main (void)
{
	//printf("Please enter the name: ");
	string user_name = GetString();
	//printf("You entered %s\n", user_name);

	if (user_name != NULL)
	{
		printf("%c", toupper( user_name[0] ));

		unsigned int i, n;
		for (i = 1, n = (unsigned int) strlen(user_name); i < n; i++)
		{
			if (user_name[i-1] == SPACE && isalpha( user_name[i] ) )
			{
				printf("%c", toupper( user_name[i] ));
			}
		}
    printf("\n");
	}
}