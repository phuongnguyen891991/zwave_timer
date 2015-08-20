#include "vnode.h"
#include "utils.h"


int allocateGroupList(GROUPLIST_t **grouplist)
{
    GROUPLIST_t* newlist=(GROUPLIST_t*)malloc(sizeof(GROUPLIST_t));
    if (newlist==NULL)
    {
        mainlog(logDebug,"Cannot create new grouplist!");
        return -1;
    }
    newlist->head=NULL;
    newlist->tail=NULL;
    newlist->size=0;
    *grouplist=newlist;
    return 0;
}
int addGroupToList(uint8_t GroupID,GROUPLIST_t* grouplist)
{
    
    GROUP_t *current=grouplist->head;

    int size;
    size=grouplist->size;
    while(size-->0)
    {
        if (current->GroupID==GroupID)
        {
            mainlog(logDebug,"Group ID has already added!");
            return 1;
        }
        current=current->next;
    }

    GROUP_t * group=(GROUP_t*)malloc(sizeof(GROUP_t));
    if (group==NULL)
    {
        mainlog(logDebug,"Cannot creat new group!");
        return -1;
    }
    group->GroupID=GroupID;
    allocateNodeList(&(group->nodelist));
    group->next=NULL;
    if (grouplist->head==NULL)
    {
        grouplist->head=grouplist->tail=group;
    }
    else
    {
        grouplist->tail->next=group;
        grouplist->tail=group;
    }
    grouplist->size++;
    return 0;

}
int allocateNodeList(NODELIST_t **nodelist)
{
    NODELIST_t* newlist=(NODELIST_t*)malloc (sizeof(NODELIST_t));
    if (newlist==NULL)
    {
        mainlog(logDebug,"Cannot create new node list!");
        return -1;
    }
    newlist->head=NULL;
    newlist->tail=NULL;
    newlist->size=0;
    *nodelist=newlist;
    return 0;
}

int addNodeToList(uint8_t NodeID, NODELIST_t* nodelist)
{
    NODE_t *current=nodelist->head;

    int size;
    size=nodelist->size;
    while(size-->0)
    {
        if (current->NodeID==NodeID)
        {
            mainlog(logDebug,"Node ID has already added!");
            return 1;
        }
        current=current->next;
    } 


    NODE_t *node=(NODE_t*)malloc(sizeof(NODE_t));
    if (node==NULL)
    {
        mainlog(logDebug,"Cannot create new node!");
        return -1;
    }
    node->NodeID=NodeID;
    node->next=NULL;
    if (nodelist->head==NULL)
    {
        nodelist->head=nodelist->tail=node;
    }
    else
    {
        nodelist->tail->next=node;
        nodelist->tail=node;
    }
    nodelist->size++;
    return 0;
}
int removeNodeFromList(uint8_t NodeID,NODELIST_t* list)
{
    NODE_t *previous=NULL;
    NODE_t *current=list->head;

    while (current!=NULL)
    {
        if (current->NodeID==NodeID)
        {
            if (list->head==current) list->head=current->next;
            if (list->tail==current) list->tail=previous;

            if (previous!=NULL) previous->next=current->next;
            free(current);
            list->size--;
            return 0;
        }
        previous=current;
        current=current->next;
    }
    return -1;
}
int  removeGroupFromList(uint8_t GroupID,GROUPLIST_t* list)
{
    GROUP_t *previous=NULL;
    GROUP_t *current=list->head;

    while (current!=NULL)
    {
        if (current->GroupID==GroupID)
        {
            if (list->head==current) list->head=current->next;
            if (list->tail==current) list->tail=previous;

            if (previous!=NULL) previous->next=current->next;

            removeAllNodeFromList(current->nodelist);
            free(current);
            list->size--;
            return 0;
        }
        previous=current;
        current=current->next;
    }
    return -1;
} 
int  removePopGroupFromList(GROUPLIST_t* list)
{
    GROUP_t *current=list->head;
    list->head=current->next;
    removeAllNodeFromList(current->nodelist);
    free(current);
    list->size--;
    return 0;
}
int  removePopNodeFromList(NODELIST_t* list)
{
    NODE_t *current=list->head;
    list->head=current->next;
    free(current);
    list->size--;
    return 0;
}
int  removeAllGroupFromList(GROUPLIST_t* list)
{
    while(list->head!=NULL)
    {
        removePopGroupFromList(list);
    }
    return 0;
}
int  removeAllNodeFromList(NODELIST_t* list)
{
    while(list->head!=NULL)
    {
        removePopNodeFromList(list);
    }
    return 0;
}
void printGroupInList(GROUPLIST_t* list)
{
    GROUP_t *current=list->head;
    int size;
    size=list->size;
    while (size-->0)
    {
        mainlog(logInfo,"GROUPID=0x%02X",current->GroupID);
        printNodeInList(current->nodelist);
        current=current->next;
    }
}
void printNodeInList(NODELIST_t* list)
{
    NODE_t *current=list->head;
    int size;

    size=list->size;
    while (size-->0)
    {
        mainlog(logInfo,"\tNODE ID=0x%02X",current->NodeID);
        current=current->next;
    }
    
}
int addNodeToGroup(uint8_t NodeID,uint8_t GroupID,GROUPLIST_t* list)
{
    GROUP_t *current=list->head;
    int size;
    int ret;
    size=list->size;
    while (size-->0)
    {
        if (current->GroupID==GroupID)
        {
            ret=addNodeToList(NodeID,current->nodelist);
            return ret;
        }
        current=current->next;
    }
    mainlog(logDebug,"No GROUPID=0x%02X in this grouplist!",GroupID );
    return -2;
}
int removeNodeFromGroup(uint8_t NodeID, uint8_t GroupID, GROUPLIST_t* list)
{
    GROUP_t *current=list->head;
    int size;
    int ret;

    size=list->size;
    while (size-->0)
    {
        if (current->GroupID==GroupID)
        {
            ret=removeNodeFromList(NodeID,current->nodelist);
            return ret;
        }
        current=current->next;
    }
    mainlog(logDebug,"No GROUPID=0x%02X in this grouplist",GroupID );
    return -2;
}
int extractNodesFromList(NODELIST_t* list,uint8_t* buffer,uint8_t* buffer_len)
{
    NODE_t *current=list->head;
    int size;
    int i=0;

    size=list->size;
    while(size-->0)
    {
        buffer[i++]=current->NodeID;
        current=current->next;
    }
    *buffer_len=list->size;
    return 0;
}

int extractNodesFromGroup(uint8_t GroupID,GROUPLIST_t* list, uint8_t* buffer,uint8_t* buffer_len)
{
    GROUP_t *current=list->head;
    int size;

    size=list->size;
    while (size-->0)
    {
        if (current->GroupID==GroupID)
        {
            extractNodesFromList(current->nodelist,buffer,buffer_len);
            return 0;
        }
        current=current->next;
    }
    mainlog(logDebug,"No GROUPID=%x in this grouplist!",GroupID );
    return -1;
}
int extractGroupsFromList(GROUPLIST_t* list, uint8_t* buffer,uint8_t* buffer_len)
{
    GROUP_t *current=list->head;
    int size;
    int i=0;
    size=list->size;
    *buffer_len=size;
    while (size-->0)
    {
        buffer[i++]=current->GroupID;
        current=current->next;
    }
    return 0;
}
