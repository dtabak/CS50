#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    int i;
    int j;
    int k;
    for (i = 1; i < n + 1; i++)
    {
        {
            for (j = n - i; j > 0; j--)
                printf(" ");
        }
        {
            for (k = 1; k <= i; k++)
                printf("#");
        }
        printf("\n");
    }
}
