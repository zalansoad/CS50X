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
        for(int j = i + 1; j < 4; j++)
        {
            if(szamok[j] < szamok[i])
            {
            int temp = szamok[i];
            szamok[i] = szamok[j];
            szamok[j] = temp;
            }
        }
    }

}