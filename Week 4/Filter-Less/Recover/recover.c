#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid argument
    if (argc != 2)
    {
        printf("Please enter only one file name\n");
        return 1;
    }
    else
    {

    FILE *raw_file_ptr = fopen(argv[1], "r");

    // Check if file is opening
    if (raw_file_ptr == NULL)
    {
        printf("File is not opening\n");
        return 1;
    }

    int counter = 0;
    char filename[8];
    BYTE buffer[512];
    FILE *jpg_file_ptr = NULL;

    while (fread(&buffer, 512, 1, raw_file_ptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!(counter == 0))
            {
                fclose(jpg_file_ptr);
            }

            sprintf(filename, "%03d.jpg", counter);
            jpg_file_ptr = fopen(filename, "w");
            counter++;
        }

        if (!(counter == 0))
        {
            fwrite(&buffer, 512, 1, jpg_file_ptr);
        }
    }

    fclose(raw_file_ptr);
    fclose(jpg_file_ptr);

    return 0;
    }
}
