#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
void print_bulb(int bit);

int main(void)
{
    //prompt user
    string input = get_string("Enter message:\n");
    int length = strlen(input);
    //substract 1 from bits in byte because array function already counts 0 as number 1
    int BITS_IN_BYTE_ARRAY = BITS_IN_BYTE - 1;
    int binary_output[BITS_IN_BYTE_ARRAY];

    for (int i = 0; i < length; i++)
    {
        //assign 0 or 1 going backwards in the array
        int x = input[i];
        for (int l = BITS_IN_BYTE_ARRAY; l >= 0; l--)
        {
            int modular = x % 2;
            int divide = x / 2;
            binary_output[l] = modular;
            x = divide;
            //printf("%i   ", divide);
        }
        //go through the array front side and print out light bulbs
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            int y = binary_output[j];
            print_bulb(y);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
