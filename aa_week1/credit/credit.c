#include <cs50.h>
#include <stdio.h>

long get_input();
int calc_length(long card);
int calc_checksum(long card, int length);
bool checksum_valid(int checksum);
int get_strating_digits(long card);

int main(void)
{
    //get credit card from user
    long card = get_input();

    //length
    int length = calc_length(card);

    //checksum
    int checksum = calc_checksum(card, length);
    bool valid = checksum_valid(checksum);

    if (valid == true)
    {
        int starting_digits = get_strating_digits(card);
        //printf("%i starting digits\n", starting_digits);

        if (starting_digits >= 40 && starting_digits < 50)
        {
            if (length == 13 || length == 16)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (starting_digits == 34 || starting_digits == 37)
        {
            if (length == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (starting_digits >= 51 && starting_digits <= 55)
        {
            if (length == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }

    //printf("%i length\n", length);
    //printf("%i checksum\n", valid);


}

//input card number
long get_input(void)
{
    long get_input;
    do
    {
        get_input = get_long("Enter number of credit card\n");
    }
    while (get_input <= 0);

    return get_input;
}

//calc length function by div by 10 and truncking ending
int calc_length(long card)
{
    int length = 0;

    do
    {
        long x = card / 10;
        card = x;
        length++;
    }
    while (card > 0);
    return length;
}

//calc checksum by using remainders with 10
int calc_checksum(long card, int length)
{
    int checksum = 0;

    for (int i = 1; i < length + 1; i++)
    {
        int current_number = card % 10;
        if (i % 2 == 0)
        {
            current_number = current_number * 2;

            if (current_number > 9)
            {
                int y = current_number % 10;
                int z = current_number / 10;
                checksum = checksum + z + y;
            }
            else
            {
                checksum = checksum + current_number;
            }
        }
        else
        {
            checksum = checksum + current_number;
        }
        long nextcard = card / 10;
        card = nextcard;
    }
    return checksum;

}

//does card satisfy checksum
bool checksum_valid(int checksum)
{
    if (checksum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//get strating digits
int get_strating_digits(long card)
{
    long strating_digits = 0;
    do
    {
        strating_digits = card / 10;
        card = strating_digits;
    }
    while (card > 99);

    return strating_digits;
}
