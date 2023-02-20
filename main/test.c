#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024
#define NO_OF_LINE 256

int nomain(void)
{
    // char buff[BUZZ_SIZE];
    // FILE *f = fopen("../programs/program_1.txt", "r");
    // fgets(buff, BUZZ_SIZE, f);
    // printf("String read: %s\n", buff);
    // fclose(f);
    // return 0;

    char a[NO_OF_LINE][MAX_LENGTH];
    char *filename = "../programs/program_1.txt";
    FILE *fp = fopen(filename, "r");
    int county = 0;
    int i;
    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    // const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp)){
        // printf("%s", buffer);
        strcpy(a[county],buffer);
        // printf("The String array: %s\n",a[0]);
        // printf("The String array: %s\n",a[1]);
        county++;
    }
    for(i=0;i<county;i++){
        printf("The String array: %s",a[i]);
    }

    // close the file
    fclose(fp);

}