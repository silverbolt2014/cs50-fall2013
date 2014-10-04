/*
 * This is a program that encrypts messages using Caesar’s cipher. Your program must accept a single
 * command-line argument: a non-negative integer. Let’s call it k for the sake of discussion. If your
 * program is executed without any command-line arguments or with more than one command-line argument,
 * your program should yell at the user and return a value of 1 (which tends to signify an error)
 * immediately as via the statement below:
 */


#include <stdio.h>
#include "../../../cs50lib/cs50.c"
#include <stdlib.h> // for atoi()
#include <string.h> // for strlen()
#include <ctype.h> // for isalpah


#define UPPER_CASE_OFFSET 65
#define LOWER_CASE_OFFSET 97

/*
The function takes an ascii encoded letter converts it to a 
1. Take an ascii encoded letter and converts it to a location in a zero based index.
2. The cipher equivalent of the letter is obtained using the zero based index value of the letter
 */
int caesar_encipher(int character, int offset, int user_key)
{
	int alpha_index_value = character - offset;
	// 	printf("current_char = %i\n", current_char);
	//  printf("alpha_index_value = %i\n", alpha_index_value);
	int cipher_index_value = (alpha_index_value + user_key ) % 26;
	int char_to_print = cipher_index_value + offset;
	return char_to_print;
}

int main(int argc, string argv[])
{
	if (argc != 2)
	{
		printf("Invalid number of arguments.\n");
		printf("Proper usage: <program-name> <cipher key>\n");
		return 1;
	}

	int user_key = atoi( argv[1] );
	if (user_key <= 0)
	{
		printf("Invalid Key. The provided key must be a positive number less than 2^31 - 26 \n");
		return 1;
	}


	printf("Please enter the plaintext: ");
	string user_input_text = GetString();

	printf("You entered %s\n", user_input_text);

	for (int i = 0, length = strlen(user_input_text); i < length; i++)
	{
		char current_char = user_input_text[i];
		// printf("i = %i, %c\n", i, user_input_text[i]);
		if ( !isalpha( current_char ) )
		{
			printf("%c", current_char );
		}
		else
		{
			if ( isupper( current_char ) )
			{
				printf("%c", caesar_encipher(current_char, UPPER_CASE_OFFSET, user_key));
			}
			else if ( islower(current_char) )
			{
				printf("%c", caesar_encipher(current_char, LOWER_CASE_OFFSET, user_key));
			}
		}
	}
	printf("\n");
}
