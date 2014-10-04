/*
 * A program that encrypts messages using Vigenère’s cipher. This program
 *  must accept a single command-line argument: a keyword, k, composed
 * entirely of alphabetical characters. If your program is executed without any
 *  command-line arguments, with more than one command-line argument, or with
 *  one command-line argument that contains any non-alphabetical character,
 * your program should complain and exit immediately, with main returning 1
 * (thereby signifying an error that our own tests can detect). Otherwise, your
 *  program must proceed to prompt the user for a string of plaintext, p, which
 * it must then encrypt according to Vigenère’s cipher with k, ultimately
 *  printing the result and exiting, with main returning 0.
 */

#include <stdio.h>
#include "../../../cs50lib/cs50.c"
#include <string.h> // for strlen()
#include <ctype.h> // for isalpha

#define UPPER_CASE_OFFSET 65
#define LOWER_CASE_OFFSET 97

/*
 * Function: vigenere_encipher
 * Returns the cipher equivalent character of the parameter "character"
 */
int vigenere_encipher(int character, int offset, int user_key)
{
  
  // Shifts letters down to a 0 to 25 index range
  int alpha_index_value = character - offset;
  
  // Shift key letter to 0 to 25 index range
  int key_letter_index_value = user_key - UPPER_CASE_OFFSET;
  
	int cipher_index_value = (alpha_index_value + key_letter_index_value ) % 26;
	int char_to_print = cipher_index_value + offset;
	return char_to_print;
}


int main(int argc, string argv[])
{
	if (argc != 2)
	{
		printf("Invalid number of arguments.\n");
		printf("Proper usage: <program-name> <cipher keyword>\n");
		return 1;
	}

	string user_input_keyword = argv[1];

	// Validate user's keyword
	for (int i = 0, n = strlen(user_input_keyword); i < n; i++)
	{
		if ( !isalpha( user_input_keyword[i] ) )
		{
			printf("Invalid keyword.  Keyword must contain only alphabetic characters\n");
			return 1;
		}
		// printf("i = %i, %c\n", i, user_input_keyword[i]);
	}


	printf("Please enter the plaintext: ");
	string user_input_text = GetString();

	int keyword_length = strlen(user_input_keyword);
  int keyword_counter = keyword_length;
  int key_to_use;

	for (int i = 0, length = strlen(user_input_text); i < length; i++)
	{
		char current_char = user_input_text[i];
		// printf("i = %i, %c\n", i, current_char);
		if ( !isalpha( current_char ) )
		{
			printf("%c", current_char );
		}
		else
		{
			if ( isupper( current_char ) )
			{
				key_to_use = user_input_keyword[keyword_counter % keyword_length];
        keyword_counter++;
        
        // Since a letter regardless of its case is treated the equally
        // all keyword letter are turned to upper case to simplify the math
        printf("%c", vigenere_encipher(current_char, UPPER_CASE_OFFSET, toupper(key_to_use)));
			}
			else if ( islower(current_char) )
			{
        key_to_use = user_input_keyword[keyword_counter % keyword_length];
        keyword_counter++;
				printf("%c", vigenere_encipher(current_char, LOWER_CASE_OFFSET, toupper(key_to_use)));
			}
		}
	}
	printf("\n");
}
