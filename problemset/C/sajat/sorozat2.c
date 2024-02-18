#include <stdio.h>
#include <cs50.h>

int szamok[] = {5, 6, 2, 1};
void sorozat(void);

int main(void)
{
    sorozat();
    for(int i = 0; i < 4; i++)
    {
        printf("%i ", szamok[i]);
    }
    printf("\n");
}

void sorozat(void)
{
    for(int i = 0; i < 4 - 1; i++)
    {
        for(int j = 0; j < 4-1-i; j++)
        {
            if(szamok[j] > szamok[j+1])
            {
            int temp = szamok[j];
            szamok[j] = szamok[j+1];
            szamok[j+1] = temp;
            }
        }
    }

}