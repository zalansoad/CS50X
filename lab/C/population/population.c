#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("What's the start size? ");
    }
    while (start_size < 9);
    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("What's the end size? ");
    }
    while (end < start_size);

    int years = 0;
    // TODO: Calculate number of years until we reach threshold
    while (start_size < end)
    {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
