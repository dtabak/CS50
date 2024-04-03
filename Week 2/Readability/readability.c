#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: \n");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float l = (letters * 1.0) / (words * 1.0) * 100;
    float s = (sentences * 1.0) / (words * 1.0) * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int i;
    int n = strlen(text);
    int counter = 0;
    for (i = 0; i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            counter++;
        }
        else
        {
            counter += 0;
        }
    }
    return counter;
}

int count_words(string text)
{
    int i;
    int n = strlen(text);
    int counter = 1;
    for (i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            counter++;
        }
        else
        {
            counter += 0;
        }
    }
    return counter;
}

int count_sentences(string text)
{
    int i;
    int n = strlen(text);
    int counter = 0;
    for (i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
        else
        {
            counter += 0;
        }
    }
    return counter;
}
