#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask the user for input for height of tower
    int h;
    do
    {
        h = get_int("Enter height\n");
    }
    while (h < 1 || h > 8);

    int x = h - 2;

    for (int row = 0; row < h; row++)
    {
        for (int i = 0; i <= x; i++)
        {
            printf(" ");
        }
        x--;

        for (int j = 0; j <= row; j++)
        {
            printf("#");
        }
        
        printf("  ");

        for (int k = 0; k <= row; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}