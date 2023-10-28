 #include "defaultheader.h"

//Make all arguments on the command into uppercase, it will numbers 

int main(int argc, char *argv[])
{
    
    for(int i = 1; i < argc; i++)
    {   
        for(int j = 0; argv[i][j] != '\0'; j++)
        {
            printf("%c", toupper(argv[i][j]));
        }

        printf(" ");
    }
} 