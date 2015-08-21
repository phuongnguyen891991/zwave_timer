#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linked_list.h"

struct linked_list * head = NULL;
struct linked_list * curr = NULL;

struct linked_list * create_list(timer_t * timerid , void (*handler))
{
	struct linked_list * lst = (struct  linked_list*)malloc(sizeof(struct linked_list));
	if(lst == NULL)
	{
		printf("\n Create fail \n");
		return NULL;
	}	
	lst->timerid = timerid;
	lst->handler = handler;
	lst->size = 0;
	lst->next = NULL;
	head = curr = lst;
	return lst;
}

struct linked_list * add_to_list(timer_t * timerid,void (*handler),bool ad_to_end)
{
	if(head == NULL)
	{
		return(create_list(timerid,handler));
	}

	struct linked_list * lst = (struct  linked_list*)malloc(sizeof(struct linked_list));
	if(lst == NULL)
	{
		printf("\n node create fail \n");
		return NULL;
	}
	lst->timerid  = timerid;
	lst->handler = handler;
	lst->next = NULL;
	if(ad_to_end)
	{
		curr->next = lst;
		curr = lst;
	}
	else
	{
		lst->next = head;
		head = lst;
	}
	lst->size ++;
	return lst;
}
struct linked_list * search_in_list(timer_t * timerid,struct linked_list **prev)
{
	struct linked_list *lst = head;
	struct linked_list *tmp = NULL;
	bool found = false;
	if(lst->timerid == timerid)
	{
		found = true;
		exit(EXIT_SUCCESS);
	}
	else
	{
		tmp = lst;
		lst = lst->next;
	}
	if(found == true)
	{
		if(prev)
			*prev = tmp;
		return lst;
	}
	else
	{
		printf("FAIL \n");
		return NULL;
	}
}
void print_list(void)
{
    struct linked_list *lst = head;

    printf("\n -------Printing list Start------- \n");
    while(lst != NULL)
    {
        printf("\nTimer [%p]  -- [%p] --[%p] --[%d]",lst->timerid,lst->handler,lst->next,lst->size);
        lst = lst->next;
    }
    printf("\n -------Printing list End------- \n");

}

void find_list(timer_t *timerid)
{
    struct linked_list *lst = head;
    timer_t * timer_compare;

    //printf("\n -------Finding list Start------- \n");
    while(lst != NULL)
    {
    	timer_compare = lst->timerid;
    	if(timer_compare == timerid)
    	{
    		//printf("\nTimer [%p]  -- [%p] --[%p] --[%d] \n",lst->timerid,lst->handler,lst->next,lst->size);
    		lst->handler();
    	}
    	
        //printf("\nTimer [%p]  -- [%p] --[%p] --[%d]",lst->timerid,lst->handler,lst->next,lst->size);
        lst = lst->next;
    }
    //printf("\n -------Findting list End------- \n");

}
