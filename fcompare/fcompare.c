#define _GNU_SOURCE    /* Needed to expose statx() function in glibc */
#include <sys/stat.h>  /* Required according to man page for statx() */
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <locale.h>
#include <pwd.h>
#include <grp.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <libgen.h>
#include <stdbool.h> 
#include <stdlib.h> //to use exit
#include <unistd.h> //to get getopt


//count the number of operations exist -> if number of operation is more than 1 then error

bool countnumofoptions(int argc, char *argv[])
{
    int optioncount = 0;

    for (int i = 0; i < argc; i++)
    {
        for(int j = 0; j < argc; j++)
        {
          if(argv[i][0] == '-' && (argv[i][j] == 'a' ||  argv[i][j] == 'b' ||  argv[i][j] == 'c' ||  argv[i][j] == 'm' ||  argv[i][j] == 's' ||  argv[i][j] == 'u'))
          {
            optioncount++;
          }   
        }
    }

    if(optioncount == 1)
        return true;
    else //if no operation is specified then it will error and exit 
        {
                        printf("\nOperations wrong amount");

            return false;
            exit(1); //does this exit out of the program or just the function
        }
}

/*Function taken for showstat.c by Stewart Weiss*/
void print_time(const char* label, struct statx_timestamp *time_field)
{
    struct tm *bdtime;                 /* Broken-down time                 */
    char       formatted_time[100];    /* String storing formatted time    */
    char       timezone[32];           /* To store time offset             */
    time_t     time_val;               /* For converted tv_sec field       */

    time_val = time_field->tv_sec;          /* Convert to time_t           */
    bdtime = localtime(&time_val);          /* Convert to broken-down time */
    if (bdtime == NULL)                     /* Check for error             */
        fprintf(stderr, "localtime failed");

    /* Create a string from the broken down time. */
    if ( strftime(formatted_time, sizeof(formatted_time), "%F %T", bdtime) == 0 )
        fprintf(stderr,"strftime failed\n");

    printf("%s%s.%09u", label, formatted_time, time_field->tv_nsec );
    if ( 0 == strftime(timezone, 32, " %z", bdtime) )
        fprintf(stderr, "Error printing time zone\n");
    printf("%s\n", timezone);
}

int main(int argc, char *argv[])
{//main start bracket

    /*ERROR HANDLING*/
    /*Invalid reoccurances of operations on command line = Error*/
    if (countnumofoptions(argc, argv) == false)
    exit(1);

    /* At least one filename must be given. If none, no error. Outputs nothing. */
    if (optind >= argc) 
    exit(0);
    /****************************************************************************/

    struct statx statx_buffer;    /* statx structure filled by statx()        */
    unsigned int mask = STATX_ALL; /* mask to pass to statx()                  */
    int          report_on_link = AT_SYMLINK_NOFOLLOW;  /* Flag indicating whether to report on link*/
    ssize_t      nbytes;          /* Return value of readlink()               */
    char         target[256];
    bool r_option = false; 
    int operations;
    char foundoperation;

    /*Create a struct to store file data for comparing later*/
    struct FileData
    {
        char filename[100];
        long long int size;
        double seconds; //change time into seconds to compare them
    };

        /*Option Parsing*/
        while((operations = getopt(argc, argv, "abcmsurl")) != -1)
        {
            switch(operations)
            {
                case 'a':
                {
                    //determine the metadata by which the files are compared by their times of last access
                    printf("This is a\n");
                    foundoperation = 'a';
                    break;
                }

                case 'b': // By their birth times
                {
                    printf("This is b");
                    foundoperation = 'b';
                    break;
                }

                case 'c': // By their times of last status change

                {
                    printf("This is c");
                    foundoperation = 'c';
                    break;
                }

                case 'm': // By their times of last modification

                {
                    printf("This is m");
                    foundoperation = 'm';
                    break;
                }

                case 's': // By their apparent size

                {
                    printf("This is s");
                    foundoperation = 's';
                    break;
                }

                case 'u': // By their disk usage

                {
                    printf("This is u");
                    foundoperation = 'u';
                    break;
                }

                case 'r':
                {
                    r_option = true;
                    break;
                }

                case 'l':
                {
                    report_on_link = 0;
                    break;
                }

                case '?' :
                fprintf(stderr,"Found invalid option %c\n", optopt);
            }
        }
   
        /* For each file argument, call statx() and print its metadata. */
        for (int i = optind; i < argc; i++) 
        {
            if (statx(AT_FDCWD, argv[i], report_on_link, mask, &statx_buffer) < 0 )
            printf("Failed to stat file named '%s'\n", argv[i]);

            /*If the files are valid, else statement will run*/
            else
            {
                if(r_option == false)
                {
                        if(foundoperation == 'a')
                        {
                            if(statx_buffer.stx_mask & STATX_ATIME)
                            {
                                if(report_on_link == 0)
                                {
                                    //SYM LINK
                                }
                                printf("File: %s", argv[i]);
                                print_time("\nLast Access: ", &statx_buffer.stx_atime);
                                if ( i < argc-1 )
                                printf("----------------------------------"
                                "-----------------------------------------\n");
                            }
                            else
                            printf("Cannot access data for '%s'", argv[i]);
                            
                        }

                        else if(foundoperation == 'b')
                        {
                            if(statx_buffer.stx_mask & STATX_BTIME)
                            {
                                printf("File: %s", argv[i]);
                                print_time("\nBirth: ", &statx_buffer.stx_btime);
                                if ( i < argc-1 )
                                printf("----------------------------------"
                                "-----------------------------------------\n");
                            }
                            else
                            fprintf(stderr, "'%s' is unavailable for comparison.", argv[i]);
                            
                        }

                        else if(foundoperation == 'c')
                        {
                            if(statx_buffer.stx_mask & STATX_CTIME)
                            {
                                printf("File: %s", argv[i]);
                                print_time("\nLast Status Change: ", &statx_buffer.stx_ctime);
                                if ( i < argc-1 )
                                printf("----------------------------------"
                                "-----------------------------------------\n");
                            }
                            else
                            printf("Cannot access data for '%s'", argv[i]);
                            
                        }

                        else if(foundoperation == 'm')
                        {
                            printf("File: %s", argv[i]);
                            print_time("\nLast Modification: ", &statx_buffer.stx_mtime);
                            if ( i < argc-1)
                            printf("----------------------------------"
                            "-----------------------------------------\n");
                        }

                        else if(foundoperation == 's')
                        {
                            if(statx_buffer.stx_mask & STATX_SIZE)
                            {
                                printf("File: %s", argv[i]);
                                printf("\nApparent size: %llu\n", statx_buffer.stx_size);
                                if ( i < argc-1 )
                                printf("----------------------------------"
                                "-----------------------------------------\n");
                            }
                            else
                            printf("Cannot access data for '%s'", argv[i]);
                        }

                        else if(foundoperation == 'u')
                        {
                            if (statx_buffer.stx_mask & STATX_BLOCKS)
                            {
                                printf("File: %s", argv[i]);
                                printf("\nApparent size: %llu\n", statx_buffer.stx_blocks);

                                if ( i < argc-1 )
                                printf("----------------------------------"
                                "-----------------------------------------\n");
                            }
                            else
                            printf("Cannot access data for '%s'", argv[i]);
                        }
                }
                
                /*If user wants link's target stat*/
            }
        }
}//main end bracket

