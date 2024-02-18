#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int szam = 0;
    for(int i = 0; i < 4; i++)
    {
        szam += i;
    }
    printf("%i \n", szam);
}