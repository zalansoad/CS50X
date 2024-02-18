#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string input);
int count_words(string input);
int count_sentence(string input);

int main(void)
{
    string text = get_string("Text: ");
    printf("Letters: %i\n", count_letters(text));
    printf("Words: %i\n", count_words(text));
    printf("Sentences: %i\n", count_sentence(text));

    float L = (count_letters(text) / (float) count_words(text)) * 100;
    float S = (count_sentence(text) / (float) count_words(text)) * 100;

    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string input)
{
    int letters = 0;
    int l = strlen(input);
    for (int i = 0; i < l; i++)
    {
        if (islower(input[i]))
        {
            letters += 1;
        }
        if (isupper(input[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int count_words(string input)
{
    int words = 0;
    int l = strlen(input);
    for (int i = 0; i < l; i++)
    {
        if (isblank(input[i]))
        {
            words += 1;
        }
    }
    return words + 1;
}

int count_sentence(string input)
{
    int sentences = 0;
    int l = strlen(input);
    for (int i = 0; i < l; i++)
    {
        if (input[i] == '!')
        {
            sentences += 1;
        }
        if (input[i] == '?')
        {
            sentences += 1;
        }
        if (input[i] == '.')
        {
            sentences += 1;
        }
    }
    return sentences;
}