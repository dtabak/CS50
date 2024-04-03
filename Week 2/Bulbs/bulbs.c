#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

int main(void)
{
    string text = get_string("Text: ");

    int i;
    int j;
    int bits[BITS_IN_BYTE - 1];
    int length = strlen(text);

    for (i = 0; i < length; i++)
    {
        for (j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            if (text[i] % 2 == 0)
            {
                bits[j] = 0;
                text[i] = text[i] / 2;
            }
            else if (text[i] % 2 == 1)
            {
                bits[j] = 1;
                text[i] = (text[i] - 1) / 2;
            }
        }
        for (int k = 0; k < 8; k++)
        {
            if (bits[k] == 0)
            {
                // Dark emoji
                printf("\U000026AB");
            }
            else if (bits[k] == 1)
            {
                // Light emoji
                printf("\U0001F7E1");
            }
        }

        printf("\n");
    }
}
