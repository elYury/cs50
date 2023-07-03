#include <cs50.h>
#include <stdio.h>


int main(void)
{

long card = 4003600000000014;
int checksum = 0;

    int length = 0;
    long cardlength = card;
    do
    {
        long x = cardlength/10;
        cardlength = x;
        length++;
    }
    while(cardlength > 0);

    printf("%i\n", length);


    for (int i = 1; i < length + 1; i++)
    {
        int current_number = card % 10;
        if (i % 2 == 0)
        {
            current_number = current_number*2;

            if(current_number > 9)
            {
                int y = current_number % 10;
                //printf("%i\n", y);
                int z = current_number / 10;
                //printf("%i\n", z);
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
            //printf("%i checksum\n", checksum);
            //printf("%i current number\n\n", current_number);
            card = nextcard;
    }


}
