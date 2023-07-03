#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

string get_input();
int calc_sentences(string get_input);
int calc_words(string get_input);
int calc_letters(string get_input);

int main(void)
{
    string input = get_input();
    //Coleman-Liau index = 0.0588 * (mu N of letters/100words) - 0.296 * (mu N of sentences/100 words) - 15.8
    int letters = calc_letters(input);
    int words = calc_words(input);
    int sentences = calc_sentences(input);

    double letters100 = (float) letters * 100 / (float) words;
    double sentences100 = (float) sentences * 100 / (float) words;

    double CLindex = 0.0588 * letters100 - 0.296 * sentences100 - 15.8;

    int answer = round(CLindex);

    //printf("%i letters\n", letters);
    //printf("%i words\n", words);
    //printf("%i sentences\n", sentences);
    //printf("%f Coleman-Liau index\n", CLindex);

    if (CLindex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (CLindex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", answer);
    }
}

//prompt input
string get_input(void)
{
    string get_input;
    do
    {
        get_input = get_string("Enter sentence:\n");
    }
    while (get_input <= 0);

    return get_input;
}

//calc number of words
int calc_words(string get_input)
{
    int x = strlen(get_input);
    int y = 0;
    for (int i = 0; i < x; i++)
    {
        if (isspace(get_input[i]))
        {
            y++;
        }

    }
    if (x > 0)
    {
        y++;
    }
    return y;
}
//calc number of sentences
int calc_sentences(string get_input)
{
    int x = strlen(get_input);
    int y = 0;
    for (int i = 0; i < x; i++)
    {
        //check for ASCII char for "!" or "." or "?"
        if (get_input[i] == 33 || get_input[i] == 46 || get_input[i] == 63)
        {
            y++;
        }

    }
    return y;
}

//calc number of letters
int calc_letters(string get_input)
{
    int x = strlen(get_input);
    int y = 0;
    for (int i = 0; i < x; i++)
    {
        if (isalpha(get_input[i]))
        {
            y++;
        }

    }
    return y;
}