#define _GNU_SOURCE
#define _XOPEN_SOURCE >= 500
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h> 

int main(int argc, char *argv[])
{
   struct tm arg2 = {0}; //Sets all struct values to 0
   struct tm arg1 = {0}; //tm must be initialized before the calling strptime
   time_t arg2_t, arg1_t;

    switch (argc)
    {
    case 1:
        fprintf(stderr, "Error: Not enough arguments. FORMAT: YYYY-DD-MM");
        break;
    
    case 2: 
        getdate(argv[1],arg1); /*stores date values into broken down time*/
        break;

    case 3: 
        getdate(argv[1],arg1); getdate(argv[2],arg2);

        if(getdate_r(argv[1],arg1) != 0 || getdate_r(argv[2],arg2) != 0)
        {
            fprintf(stderr,"Failed to convert given input. FORMAT: YYYY-DD-MM");
            exit (1);
        }

        arg2_t = mktime(&arg2); /*mktime : broken down time -> time_t */
        arg1_t = mktime(&arg1);

        long double seconds = difftime(arg2_t,arg1_t); /*needs a time_t format*/
        int days = seconds / 86400;
        break;
    }
}