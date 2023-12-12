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

void print_time(const char* label, struct statx_timestamp *time_field)
{
    struct tm *bdtime;                 /* Broken-down time                 */
    char       formatted_time[100];    /* String storing formatted time    */
    char       timezone[32];           /* To store time offset             */
    time_t     time_val;               /* For converted tv_sec field       */

    time_val = time_field->tv_sec;          /* Convert to time_t           */
    bdtime = localtime(&time_val);          /* Convert to broken-down time */
    
    if (bdtime == NULL)                     /* Check for error             */
        fprintf(stderr, "localtime");

    /* Create a string from the broken down time. */
    if ( strftime(formatted_time, sizeof(formatted_time), "%F %T", bdtime) == 0 )
        fprintf(stderr,"strftime failed\n");

    printf("%s%s.%09u", label, formatted_time, time_field->tv_nsec );
    if ( 0 == strftime(timezone, 32, " %z", bdtime) )
        fprintf(stderr, "Error printing time zone\n");
    printf("%s\n", timezone);
}

int main(int argc, char *argv[])
{
    int report_on_link = AT_SYMLINK_NOFOLLOW;
    unsigned int mask = STATX_ALL;
    struct statx stx;    /* statx structure filled by statx()        */
    statx(AT_FDCWD, argv[1], report_on_link,  mask, &stx);
    printf("Last status change:  %llu", stx.stx_size); //doesnt need a &
    print_time("\nLast Access: ", &stx.stx_atime); //Need to add & because stx_atime returns a time structure 
    //unlike stx.stx_size, which only returns an int value!!
    printf("\nhi");
    
} //next steps: learn how to use statx(fd, pathway, symlink follow?, mask, storage struct)
    // Note: 

/*Directory structure
Stat struct 
utmp struct 
password struct
io (read/write)
properities of files/directories [chapter 1 stuff]
Who created linux

struct stat stx;   
lstat(argv[1], &stx); //this connects the argument to the struct
printf("Last status change:  %s", ctime(&stx.st_ctime));*/
