#include <time.h>
#include "currTime.h"

#define BUF_SIZE 1000

char *currTime(const char *format)
 {
     static char buf[BUF_SIZE];  /* Nonreentrant */
     time_t t;
     size_t s;
     struct tm *tm;
 
     t = time(NULL);
     tm = localtime(&t);
     if (tm == NULL)
         return NULL;
 
     s = strftime(buf, BUF_SIZE, (format != NULL) ? format : "%c", tm);
 
     return (s == 0) ? NULL : buf;
 }
