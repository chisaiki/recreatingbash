#include <stdio.h>

int main(int argc, char *argv[])
{
    switch(argc)
    { 
        case 1: //Error: I initially typed case '1', this results in an error because argc is an int not char!
        fprintf(stderr, "Error: Not Enough Arguments.");
        break;

        case 2:
        break;

        case 3: 
        break;
    }
}