#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//we define what is a BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //if more than one file name return error
    if (argc != 2)
    {
        printf("usage: ./recover FILENAME");
        return 1;
    }
    FILE *input_pointer = fopen(argv[1], "r");

    //if there is no file return error
    if (input_pointer == NULL)
    {
        printf("Error: No file found");
        return 1;
    }
    //initialize
    int count = 0;
    //buffer is the size of the blocks where the image can be 512 bytes
    BYTE buffer[512];
    //address where we are currently looking at
    FILE *img_pointer = NULL;
    //filename
    char filename[8];

    //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
    //we continue reading until there are no bytes to read (== 1 there are. == 0 there are not)
    //&buffer is the address of the buffer array, 512 is the size, how big are the elements 1 = 1 byte, input (where is the file getting the info from)
    while (fread(&buffer, 512, 1, input_pointer) == 1)
    {
        //0xff 0xd8 0xff 0xe"X"
        //the start of each new file will look like this as this header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if its not the first file then close the last file, because we found a new one
            if (!(count == 0))
            {
                fclose(img_pointer);
            }
            //sprintf sends a formated output to a string, so we change the filename using sprintf
            sprintf(filename, "%03i.jpg", count);
            //this time we use fopen to write mode in a new file
            img_pointer = fopen(filename, "w");
            count++;
        }
        //we write the block of 512 bytes into the new memory address (img pointer)
        if (!(count == 0))
        {
            fwrite(&buffer, 512, 1, img_pointer);
        }
    }
    //close everything we are done
    fclose(img_pointer);
    fclose(input_pointer);
    return 0;
}
//img_pointer is the address of the new file
//input_pointer is the address of the input file