 #include "defaultheader.h"

//Make all arguments on the command into uppercase, it will numbers 

void printUpper(int a, char *b[])
{
    for(int i = 1; i < a; i++)
    {   
        for(int j = 0; b[i][j] != '\0'; j++)
        {
            printf("%c", toupper(b[i][j]));
        }

        printf(" ");
    }
}

int main(int argc, char *argv[])
{
    printUpper(argc, argv);
} 