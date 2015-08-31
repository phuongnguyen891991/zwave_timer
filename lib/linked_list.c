#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include "linked_list.h"

struct linked_list * head = NULL;
struct linked_list * curr = NULL;

struct linked_list * create_list(timer_t timerid , void (*handler))
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

struct linked_list * add_to_list(timer_t timerid,void (*handler),bool ad_to_end)
{
	if(head == NULL)
	{
		return(create_list(timerid,handler));
	}

	struct linked_list *lst = (struct  linked_list*)malloc(sizeof(struct linked_list));
	if(lst == NULL)
	{
		printf("\n node create fail \n");
		return NULL;
	}
	lst->timerid  = timerid;
    printf("timer in add_to_list function: [0x%lx] \n",(long)lst->timerid);
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
    struct linked_list *ptr = head;
    //struct linked_list *tmp = (struct linked_list*)malloc(sizeof(struct linked_list));
    timer_t *timer_temp;
    bool found = false;

    while(ptr != NULL)
    {
        timer_temp = ptr->timerid;
        if(timer_temp == timerid)
        {
            found = true;
            break;
        }
        else
        {
          //  tmp = ptr;
            ptr = ptr->next;
        }
    }
    if(true == found)
    {
       // if(prev)
         //   *prev = tmp;
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
        printf("\nTimer [0x%lx]  -- [0x%lx] --[0x%lx] --[..]",(long)lst->timerid,(long)lst->handler,(long)lst->next);
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
        printf("[0x%lx]\n",(long)lst->timerid);
    		lst->handler(timerid);
    	}
        lst = lst->next;
    }
}

struct linked_list *delete_from_list(timer_t *timerid,struct linked_list *first)
{
struct linked_list *prev=NULL;
  struct linked_list *root = first;
  while (root != NULL)
  {
    if (root->timerid == timerid)
    {
      if (prev != NULL && root->next != NULL) //middle elements
      {
        prev->next = root->next;
        free(root);
      }
      else if (prev == NULL) //first element
      {
        free(first);
        first = root->next;
        root = root->next;
      }
      else if (root->next == NULL) //last element
      {
        prev->next = NULL;
        free(root);
      }
    }
    prev = root;
    root = root->next;
  }
  return first;
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
     return 0;
}