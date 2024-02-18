// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Number of words in the dictionary
int words = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // toupper word
    int index = toupper(word[0]) - 'A';
    // hash the word get hash value

    // strcasecmp - case insensitive comparison
    // cusrsor - cursor= cursor->next while megvan a node vagy null
    node *cursor = table[index];
    while (cursor != NULL) // seg fault miután elkezdtük összehasonlítani a dolgokat.
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number -----------------------------------------------------------------OK
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false-------------------OK
bool load(const char *dictionary)
{
    char word[LENGTH];
    // TODO
    // open up dictionarz file / read string one by one / create a new node for word(value and nex pointer) / hash word / insert
    // node into hash table

    // fopen > check if NULL
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    // read string from file: fscanf(file, "%s", word) ezt while loopba until EOF
    while (fscanf(inptr, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node)); // chreate a new node
        if (n == NULL)
        {
            return false;
        }
        else
        {
            strcpy(n->word, word);
            n->next = NULL;
        }

        int index = hash(word); // hash word

        // insert node into hash table
        n->next = table[index];
        table[index] = n;

        // increment size
        words++;
    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // amint beolvasol egy szot ++
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
