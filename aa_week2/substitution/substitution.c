#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //---------------------------------------------------------------------------------
    //checks for correct usage
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int length_key = strlen(key);
    int same_letter_counter = 0;

    if (length_key != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int count = 0; count < length_key; count++)
    {
        if (!isalpha(key[count]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        for (int count2 = 0; count2 < length_key; count2++)
        {
            if (key[count] == key[count2])
            {
                same_letter_counter++;
            }
        }
    }

    if (same_letter_counter > 26)
    {
        printf("Key must not contain repeated letters.\n");
        printf("%i\n", same_letter_counter);
        return 1;
    }
    //---------------------------------------------------------------------------------------------

    string plain_text = get_string("plaintext: ");
    int length = strlen(plain_text);

    //assign alphabet arrays
    char lower_alphabet[25];
    for (int i = 0; i <= 25; i++)
    {
        lower_alphabet[i] = 97 + i;
    }

    char upper_alphabet[25];
    for (int i = 0; i <= 25; i++)
    {
        upper_alphabet[i] = 65 + i;
    }

    //juicy method, i find the position of where the first char of plain_text matched with alphabet then print out a char from the key with the same position
    //with 2 loops for upper and lower case, if not alpha then is prints it out as is
    printf("ciphertext: ");

    for (int i = 0; i < length; i++)
    {
        char x = plain_text[i];
        if (isupper(x)) //x >= 65 && x <= 90
        {
            for (int j = 0; j <= 25; j++)
            {
                char up_z = upper_alphabet[j];
                if (x == up_z)
                {
                    char output = toupper(key[j]);
                    printf("%c", output);
                }
            }
        }
        else if (islower(x)) //x >= 97 && x <= 122
        {
            for (int n = 0; n <= 25; n++)
            {
                char low_z = lower_alphabet[n];
                if (x == low_z)
                {
                    char output2 = tolower(key[n]);
                    printf("%c", output2);
                }
            }
        }
        else if (!isalpha(x))
        {
            printf("%c", x);
        }

    }
    printf("\n");
}
