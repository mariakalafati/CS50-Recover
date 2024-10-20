#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Insert 1 command line arguemnet\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Forensic image cannot be opened\n");
        return 1;
    }
    int count = 0;
    unsigned char buffer[512];
    char filename[50];
    FILE *img;
    do
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count != 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }
        if (count != 0)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    while (fread(buffer, 512, 1, file) == 1);
    fclose(file);
    fclose(img);
}
