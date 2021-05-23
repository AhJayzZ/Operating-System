#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main(int argc , char *argv[])
{

    if (argc < 2) {
        printf("Enter the address: ");
        return -1;
    }

    unsigned int address = atoi(argv[1]);
    unsigned int page = address / PAGE_SIZE;
    unsigned int offset = address % PAGE_SIZE;

    printf("The address %u contains :\n",address);
    printf("page number = %u\n",page);
    printf("offset = %u",offset);
        
    return 0;
}