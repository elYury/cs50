#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    //printf("%i score1\n", score1);
    //printf("%i score2\n", score2);

    //Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
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


    int score = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j <= 25; j++)
        {
            if (word[i] == upper_alphabet[j])
            {
                score += POINTS[j];
                //printf("%i score\n", score);
            }
            else if (word[i] == lower_alphabet[j])
            {
                score += POINTS[j];
                //printf("%i score\n", score);
            }
        }
    }
    return score;
}
