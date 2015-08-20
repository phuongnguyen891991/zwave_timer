#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linked_list {
	int number ;
	timer_t *timerid;
	void  (*handler)();
	struct linked_list *next;
};

struct linked_list * create_list(timer_t *timerid ,void (*handler));
struct linked_list * add_to_list(timer_t * timerid,void (*handler),bool ad_to_end);
void print_list();
struct linked_list * search_in_list(timer_t *timerid,struct linked_list ** prev);