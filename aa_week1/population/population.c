#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size = 0;
    do
    {
        start_size = get_int("Input starting population\n");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size = 0;
    do
    {
        end_size = get_int("Input ending population\n");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int current_pop = start_size;
    int years = 0;

    if (start_size != end_size)
    {
        do
        {
            current_pop = current_pop + current_pop / 3 - current_pop / 4;
            years++;
        }
        while (current_pop < end_size);
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}
