#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // one command line argument argc != 2, return 1;
    if (argc != 2)
    {
        printf("Enter one command line argument only\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // create buffer
    uint8_t buffer[512];

    char output[8];
    int i = 0;
    sprintf(output, "%03i.jpg", i);

    FILE *outptr = fopen(output, "w");
    if (outptr == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    // read 512 bytes into buffer// 0xff 0xd8 0xff
    while (fread(buffer, 1, 512, inptr) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (i == 0) // if(first jpeg)
            {
                i++;
                fwrite(buffer, 512, 1, outptr);
            }

            else // close first file + open new
            {
                fclose(outptr);
                sprintf(output, "%03i.jpg", i);
                outptr = fopen(output, "w");
                if (outptr == NULL)
                {
                    printf("Cannot open file\n");
                    return 1;
                }

                fwrite(buffer, 512, 1, outptr);
                i++;
            }
        }
        else if (i > 0)
        {
            fwrite(buffer, 512, 1, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);
}
// if (buffer indicates that it is the start of a new jpg )
//  {
//      if(first jpeg)
//          write 000.jpg

//      else
//          close first file
//          open new file
//  }
//
// else
//  keep writing
//
//
