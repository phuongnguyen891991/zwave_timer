#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef PRINT_SIGINFO
#define PRINT_SIGINFO

 void print_siginfo(siginfo_t *si);
 void handler(int sig, siginfo_t *si, void *uc);

#endif
