#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool alpha(string x);
bool similar(string x);
string cipher(string x, string y);
int main(int argc, string argv[])
{
    string key = argv[1];

    if(argc != 2)
    {
    printf("Provide one key (only)\n");
    return 1;
    }

    for(int i = 0; i < 26; i++)
    {
        if(islower(key[i]))
            {
                key[i] = toupper(key[i]);
            }
    }

    if(strlen(key) != 26)
    {
    printf("The key must be 26 characters long\n");
    return 1;
    }

    // check alpha only
        if(alpha(key) == false)
    {
        printf("The key must contain alphabetic characters only\n");
        return 1;
    }
        if(similar(key) == false)
    {
        printf("The key cannot contain the same character twice\n");
        return 1;
    }
    string plain = get_string("Text: ");
    printf("plaintext: %s\n", plain);

    printf("ciphertext: %s\n", cipher(plain, key));
}


bool alpha(string x)
{
    bool result = true;
    for(int i = 0; i < 26; i++)
    {
        if(!isalpha(x[i]))
        {
            result = false;
        }
    }
    return result;
}

bool similar(string x)
{
    bool result = true;
    for(int i = 1; i < 26; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(x[i] == x[j])
            {
            result = false;
            }
        }

    }

    return result;
}

string cipher(string x, string y)
{
    int l = strlen(x);
    for(int i = 0; i < l; i++)
    {
        if(islower(x[i]))
            {
                x[i] = tolower(y[x[i] - 'a']);
            }
        if(isupper(x[i]))
            {
                x[i] = y[x[i] - 'A'];
            }
    }
    return x;
}