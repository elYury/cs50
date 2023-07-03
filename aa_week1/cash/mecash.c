#include <cs50.h>
#include <stdio.h>

int main (void)
{
    //prompt input of cents
    int get_cents;
    do
    {
        get_cents = get_int("Enter number of cents?\n");
    }
    while (get_cents >= 100 || get_cents <= 0);

    //variable to calculate how much money we have given back
    int count = 0;

    int calculate_25 = get_cents/25;
    count = calculate_25*25;

    int calculate_10 = (get_cents - count)/10;
    count = count + calculate_10*10;

    int calculate_5 = (get_cents - count)/5;
    count = count + calculate_5*5;

    int calculate_1 = (get_cents - count)/1;
    count = count + calculate_1*1;

    printf("%i quarters\n", calculate_25);
    printf("%i dimes\n", calculate_10);
    printf("%i nickles\n", calculate_5);
    printf("%i pennies\n", calculate_1);

    //printf("%i count\n", count);
}

