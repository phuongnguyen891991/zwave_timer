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
struct linked_list * search_in_list(timer_t *timerid)
{
    struct linked_list *lst = head;
    timer_t * timer_compare;

    while(lst != NULL)
    {
        timer_compare = lst->timerid;
        if(timer_compare = timerid)
        {
           return lst;
        }
        else
        {
            return (0);
        }
        lst = lst->next;
    }
   /* struct linked_list *lst = head;
    struct linked_list *tmp = NULL;
    timer_t *timer_temp;
    bool found = false;

    while(lst != NULL)
    {
        timer_temp = lst->timerid;
        if(timer_temp == timerid)
        {
            found = true;
            break;
        }
        else
        {
            tmp = lst;
            lst = lst->next;
        }
    }
    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return lst;
    }
    else
    {
        return NULL;
    }*/
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
    		lst->handler();
    	}
        lst = lst->next;
    }
}

int delete_from_list(timer_t *timerid)
{
    struct linked_list *prev = NULL;
    struct linked_list *del = NULL;

    del = search_in_list(timerid);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
        {
            prev->next = del->next;
        }

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }
    //free(del);
    return 0;
}
int count_node()
{
    struct linked_list * temp;
     int i=0;
     temp=head;
     while(temp!=NULL)
     {
          i++;
          temp=temp->next;
     }
     printf("\n\nnumber of nodes are %d  \n",i);
}