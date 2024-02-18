#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int l = strlen(input);
    
    if (l == 1)
    {
        return input[0] - 48;
    }
    char last_digit = input[l - 1];
    int converted_digit = last_digit - 48;
    input[l - 1] = '\0';


    return converted_digit + 10 * convert(input);
}