/****************************************************************************
 *
 *
 * Copyright (c) 2014
 * Veriksytems, Inc.
 * All Rights Reserved
****************************************************************************/


#include "utils.h"

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif
uint8_t gLogLevel=99;


void hexdump(void *mem, unsigned int len)
{
    if (gLogLevel<3) return;
    unsigned int i, j;

    for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
    {
        /* print offset */
        if(i % HEXDUMP_COLS == 0)
        {
            printf("0x%06x: ", i);
        }

        /* print hex data */
        if(i < len)
        {
            printf("%02x ", 0xFF & ((char*)mem)[i]);
        }
        else /* end of block, just aligning for ASCII dump */
        {
            printf("   ");
        }

        /* print ASCII dump */
        if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
        {
            for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
            {
                if(j >= len) /* end of block, not really printing */
                {
                    putchar(' ');
                }
                else if(isprint(((char*)mem)[j])) /* printable char */
                {
                    putchar(0xFF & ((char*)mem)[j]);
                }
                else /* other char */
                {
                    putchar('.');
                }
            }
            putchar('\n');
        }
    }
}




void mainlog(uint8_t logLevel,const char *format,...)
{
    char buffer[1024];
    va_list vArgs;
    unsigned int len;
    va_start(vArgs,format);
    vsprintf((char*)buffer,(char const*)format,vArgs);
    va_end(vArgs);
    len=strlen(buffer);
    if (logLevel<=gLogLevel)
    {
        if (len<1024) printf("%s\n",buffer);
    }
}
