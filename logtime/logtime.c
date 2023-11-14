#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//Case when user includes -f option
void userfile(char *a[])
{
   if(a[2] == NULL) //Check if file was included in argument
      {
         fprintf(stderr, "ERROR: Missing Custom User File Information.");
         exit (1);
      }

   int userfile = open(a[2],O_RDONLY);
   if (userfile == -1)
   {
      fprintf(stderr, "\n'%s' not found.", a[2]);
      exit (1);
   }
}

void errhandle()
{
   int checkwtmp = open("/var/log/wtmp", O_RDONLY);
   if(checkwtmp == -1)
   {
      fprintf(stderr, "WTMP file not found.");
      exit (1);
   }
}

int main(int argc, char* argv[])
{
   
   errhandle();

   int opt; 
   while((opt = getopt(argc, argv, "af")) != -1)
   {
      switch (opt)
      {
      case 'a':
         printf("\nShow the log times for all users that have entries in the file _PATH_WTMP.\n");
         break;

      case 'f':
         userfile(argv);
         break;

      case '?' :
            printf("Found invalid option '%c'\n", optopt);
            break;

      default:
           printf ("?? getopt returned character code 0%o ??\n", opt);
           break;
      }
   }
}