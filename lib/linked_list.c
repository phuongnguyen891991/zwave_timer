#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
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
	//lst->size++;
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
	return lst;
}
struct linked_list * search_in_list(timer_t * timerid,struct linked_list **prev)
{
    struct linked_list *ptr = head;
    struct linked_list *tmp = NULL;
    bool found = false;

    while(ptr != NULL)
    {
        if(ptr->timerid = timerid)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

void print_list(void)
{
    struct linked_list *lst = head;

    printf("\n -------Printing list Start------- \n");
    while(lst != NULL)
    {
        printf("\nTimer [%p]  -- [%p] --[%p] --[..]",lst->timerid,lst->handler,lst->next);
        lst = lst->next;
    }
    printf("\n -------Printing list End------- \n");

}

void find_list_call_handler(timer_t *timerid)
{
    struct linked_list *lst = head;
    timer_t * timer_compare;

    while(lst != NULL)
    {
    	timer_compare = lst->timerid;
    	if(timer_compare == timerid)
    	{
    		//printf("\nTimer [%p]\n",lst->timerid);
    		lst->handler();
    	}
        lst = lst->next;
    }
}

int delete_from_list(timer_t *timerid)
{
    int counter = 0;
    int counter_loop = 0;
    struct linked_list *prev = NULL;
    struct linked_list *del = NULL;
    struct itimerspec its;
   // printf("\n Deleting value node from list\n");

    del = search_in_list(timerid,&prev);
    printf("[%p] \n",timerid);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
        {
            prev->next = del->next;
           // printf("1\n");
        }

        if(del == curr)
        {
            curr = prev;
          //  printf("2 \n");
        }
        else if(del == head)
        {
         
               its.it_value.tv_sec = 0;
               its.it_value.tv_nsec = 0;
               its.it_interval.tv_sec = 0;//its.it_value.tv_sec;
               its.it_interval.tv_nsec = 0;   
            head = del->next;
           // printf("3\n");
        }
    }
    free(del);
    del = NULL;

    return 0;
}
