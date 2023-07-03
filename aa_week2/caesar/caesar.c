#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool is_correct_input(int number_arguments, string key_string);
string encipher(string text, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //get key
    string key_string = argv[1];
    int number_arguments = argc;
    bool input = is_correct_input(number_arguments, key_string);

    if (input == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //get text
    string text = get_string("Enter text:\n");

    //encipher
    int key = atoi(key_string);
    string x = encipher(text, key);

    //print enciphered text
    printf("ciphertext: %s\n", x);
}

bool is_correct_input(int number_arguments, string key_string)
{
    bool correct = true;


    //check if command-line arguments are incorrect
    if (atoi(key_string) <= 0)
    {
        correct = false;
    }
    //check if input is not a digit
    int length = strlen(key_string);
    for (int i = 0; i < length; i++)
    {
        char selected_char = key_string[i];
        if (!isdigit(selected_char))
        {
            correct = false;
        }
    }
    return correct;
}

string encipher(string text, int key)
{
    int length = strlen(text);
    string cipher_text = text;

    //to handle overflow of key
    if (key > 26)
    {
        key = key % 26;
    }

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                //adds ASCII number to encrypt
                int x = text[i] + key;
                //in case of overflow it loops around the alphabet
                if (x > 90)
                {
                    x -= 26;
                }
                cipher_text[i] = x;
            }
            //same here but for lower case because it has different ASCII code
            else if (islower(text[i]))
            {
                int x = text[i] + key;
                if (x > 122)
                {
                    x -= 26;
                }
                cipher_text[i] = x;
            }

        }
    }
    return cipher_text;
}