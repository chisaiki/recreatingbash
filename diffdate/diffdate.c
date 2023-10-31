#include <stdio.h>
#include <locale.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
 
   time_t todaysdate;

   time(&todaysdate);

   printf("Todays Date = %s", ctime(&todaysdate));

/*     char buff[70];
    struct tm my_time = { .tm_year=112, // = year 2012
                          .tm_mon=9,    // = 10th month
                          .tm_mday=9,   // = 9th day
    };
 
    if (strftime(buff, sizeof buff, "%A %c", &my_time))
        puts(buff);
    else
        puts("strftime failed");
 
    setlocale(LC_TIME, "en_US.utf8");
 
    if (strftime(buff, sizeof buff, "%A %c", &my_time))
        puts(buff);
    else
        puts("strftime failed");
 */
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


/*Resources: 
https://en.cppreference.com/w/c/chrono/strftime#:~:text=Converts%20the%20date%20and%20time,to%20count%20bytes%20are%20written.
https://www.tutorialspoint.com/c_standard_library/time_h.htm
https://www.tutorialspoint.com/c_standard_library/c_function_ctime.htm
*/