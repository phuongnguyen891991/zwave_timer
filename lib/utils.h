/****************************************************************************
 *
 *
 * Copyright (c) 2014
 * Veriksytems, Inc.
 * All Rights Reserved
****************************************************************************/
#ifndef _UTIL_H_
#define _UTIL_H_
 #include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#define BIT0		0x01
#define BIT1		0x02
#define BIT2		0x04
#define BIT3		0x08
#define BIT4		0x10
#define BIT5		0x20
#define BIT6		0x40
#define BIT7		0x80

extern uint8_t gLogLevel;

enum {
    logQuerry=0,
    logWarning,
    logUI,
    logInfo,
    logDebug
};

void hexdump(void *mem, unsigned int len);

void mainlog(uint8_t logLevel,const char *format,...);

#endif
