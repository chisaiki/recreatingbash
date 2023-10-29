/****************************************************************************
  Title          : seq.c
  Author         : Syeda Rahman
  Created on     : October 26, 2023
  Description    : Print a sequence of integers based on user input
  Purpose        : To emulate the bash command seq
  Usage          : seq #startvalue(OPTIONAL) #increment(OPTIONAL) #stopvalue
  Build with     : gcc -o seq seq.c 
  Modifications  : N/A

*****************************************************************************

Copyright (C) 2023 - Syeda Rahman

This code is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/
#include "defaultheader.h"

void instruction()
{
    char check; 

    fprintf(stderr,"\nError: Not enough arguments. \nFormat: StartValue(Optional) Increment(Optional) StopValue\n \nWould you like a more detailed explanation? Type 'Y' for Yes.\n");
    scanf("%c", &check);

    if(check == 'Y' || check == 'y')
    {
        printf("\nAfter typing the program name you must provide arguments (integer values) in the following formats (see examples): \n$seq 10 : will output values from 1 and 10 \n$seq 2 10 : will output values from 2 and 10, incrememting up 1 number at a time. \n$seq 2 2 10 : will output values starting from 2 incrementing by 2 and ending at 10.\n");
    }
}

//Check if argument are valid integers before running any switch statements 
bool checkifvalid(int a, char *b[])

{
    bool checkifdigit = true;

    //iterate through each argument and check each character of each argument for any letters b[i][j] where i tells us which argument and j tells us the character were looking at the current i argument
    for(int i = 1; i < a; i++)
    {   
        int canprint = false;
        for(int j = 0 ; b[i][j] != '\0'; j++)
        {
            //This will make sure my flags won't be taken in as arguments, if it did then nothing would run
            if(b[i][j] == '-' && (b[i][j + 1] == 'f' || b[i][j + 1] == 's' || b[i][j + 1] == 'w'))
            {
                i++;
            }

            else
            {
                if(isdigit(b[i][j]) == 0 && b[i][j] != '-') 
                {
                checkifdigit = false;
                canprint = true;
                } 
            }
        }
        if(canprint == true)
        fprintf(stderr,"\n'%s' is an invalid argument. Must be numeric integer values.\n", b[i]);
    }

    return checkifdigit;
}

//if it doesnt contain any alphabet letters then it will run
int runifvalid(int a, int argc, char *argv[])
{
 if (a != 0)
    {
        switch(argc) //cases are based on the number of arguments given in command line
        {
            case 1:
            {
                instruction();
                return -1;
                break; 
            }

            //2 Arguments (Program name and int value)
            case 2:
            {
                long long int stop = atof(argv[1]);
                for(long long int i = 1; i <= stop; i++)
                    {
                        printf("%lld\n", i);
                    }
            break;
            }

            //3 Arguments (Program name and 2 int value)
            case 3:
            {
                long long int start = atof(argv[1]);
                long long int stop = atof(argv[2]);
                if(start < stop)
                {
                        while(start <= stop)
                    {
                        printf("%lld\n", start);
                        start++;
                    }
                }
                
            break;
            }

            //4 Arguments (Program name and 3 int value)
            case 4:
            {
                long long int start = atof(argv[1]);
                long long int increment = atof(argv[2]);
                long long int stop = atof(argv[3]);

                    if(increment == 0)
                    {
                        fprintf(stderr,"Error: Increment must be a non-zero value!\n");
                    }  

                    if(start > stop && increment < 0)
                    {
                        while(start >= stop)
                        {
                            printf("%lld\n", start);
                            start = start + increment;
                        }
                    }
                    else if (start < stop && increment > 0)
                    {
                        while(start <= stop)
                        {
                            printf("%lld\n", start);
                            start = start + increment;
                        }
                    }
                
            break;
            }   
        }

        return 0;
    }

    else
    {
        instruction();
        return -1;
    }  
    
}

int main(int argc, char *argv[])
{
    int opt;
    while((opt = getopt(argc, argv, "fsw")) != -1)
    {
        switch(opt)
        {
            case 'f':
            printf("yolo");
            break;

            case 's':
            printf("hi");
            break;

            case 'w':
            printf("bye");
            break;  

            case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        }
    }
    runifvalid(checkifvalid(argc, argv), argc, argv);
              
}

//need to learn about standard error stream
    
/*resources: 
https://stackoverflow.com/questions/58628804/how-do-i-use-argc-argv-to-compute-in-c
https://www.quora.com/Can-we-declare-variables-in-a-switch-case
https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html#:~:text=The%20value%20of%20the%20argc,of%20argc%20counts%20this%20element.
https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
https://www.geeksforgeeks.org/using-variable-format-specifier-c/
https://www.programiz.com/c-programming/library-function/ctype.h/isalpha
https://stackoverflow.com/questions/21136735/store-argv1-to-an-char-variable
https://stackoverflow.com/questions/43085731/getting-specific-character-values-from-argv-and-making-a-new-const-char
https://www.educba.com/stderr-in-c/
https://stackoverflow.com/questions/48367022/c-iterate-through-char-array-with-a-pointer
*/





