#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int z;
    do
    {
        z = get_int("How many stairs you want? Max 8\n");
    }
    while (z < 1 || z > 8);

    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < (z - (i + 1)); j++)
        {
            printf(" ");
        }

        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }

        printf("  ");

        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }

        printf("\n");
    }
}