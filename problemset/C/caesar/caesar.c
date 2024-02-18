#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// number if not remind user Usage: ./caesar key
// if no arg remind user Usage: ./caesar key
// if more than one argv remind user Usage: ./caesar key

bool digit(string input);
string ciphertext(string input1, int input2);

int main(int argc, string argv[])

{
    // check if one word only
    if (argc != 2)
    {
        printf("Substitute 'key' with one number only ./caesar key\n");
        return 1;
    }

    // check if digit only
    bool digitonly = digit(argv[1]);
    if (digitonly == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (argv[1] < 0)
    {
        printf("Usage: ./caesar key\n");
    }

    int k = atoi(argv[1]);
    string plaintext = get_string("Text: ");
    printf("Plaintext: %s\n", plaintext);

    string cipher = ciphertext(plaintext, k);
    printf("Ciphertext: %s\n", cipher);
}

bool digit(string input)
{
    bool result = true;

    int l = strlen(input);
    for (int i = 0; i < l; i++)
    {
        if (!isdigit(input[i]))
        {
            result = false;
        }
    }
    return result;
}

string ciphertext(string input1, int input2)
{
    int l = strlen(input1);
    for (int i = 0; i < l; i++)
    {
        if (islower(input1[i]))
        {
            input1[i] = input1[i] - 97;
            input1[i] = (input1[i] + input2) % 26;
            input1[i] = input1[i] + 97;
        }
        if (isupper(input1[i]))
        {
            input1[i] = input1[i] - 65;
            input1[i] = (input1[i] + input2) % 26;
            input1[i] = input1[i] + 65;
        }
    }
    return input1;
}
