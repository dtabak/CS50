// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);

    //Access linked list at that index in hash table
    node *n = table[hash_value];

    while (n != NULL)
    {
        if(strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int i=0;
    int a=1;
    int total=0;
    while (i< strlen(word))
    {
        total += toupper(word[i])*a;
        i++;
        a += 2;
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary file
    FILE * dict_pointer = fopen (dictionary, "r");

    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Initialize word array
    char next_word[LENGTH +1];

    while (fscanf(dict_pointer, "%s", next_word) != EOF)
    {
        //create a node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, next_word);
        int hash_value = hash(next_word);

        //insert node into hash table
        n->next = table[hash_value];
        table[hash_value] = n;
        dictionary_size++;
    }
    fclose(dict_pointer);

return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    //iterate over hash table
    for (int i = 0; i < N; i++)
{
    node *pointer = table[i];

    while (pointer != NULL)
    {
        node *tmp = pointer;
        pointer = pointer->next;
        free(tmp);
    }
}

return true;

}
