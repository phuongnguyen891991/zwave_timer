#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linked_list {
	int number ;
	timer_t *timerid;
	void  (*handler)();
	//int *size ;
	struct linked_list *next;
};

struct linked_list * create_list(timer_t *timerid ,void (*handler));
struct linked_list * add_to_list(timer_t * timerid,void (*handler),bool ad_to_end);
void print_list();
struct linked_list * search_in_list(timer_t *timerid);
void find_list_call_handler(timer_t *timerid);
int delete_from_list(timer_t *timerid_tmp);
int count_node();
