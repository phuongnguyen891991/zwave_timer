#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct NODE 
{
	uint8_t NodeID;
	struct NODE *next;
}NODE_t;

typedef struct NODELIST
{
	struct NODE *head;
	struct NODE *tail;
	int size;
}NODELIST_t;

typedef struct GROUP 
{
	uint8_t GroupID;
	NODELIST_t *nodelist;
	struct GROUP *next;
}GROUP_t;

typedef struct GROUPLIST
{
	struct GROUP *head;
	struct GROUP *tail;
	int size;
}GROUPLIST_t;

int 	allocateGroupList(GROUPLIST_t **grouplist);
int  	addGroupToList(uint8_t GroupID,GROUPLIST_t* grouplist);
int 	allocateNodeList(NODELIST_t **nodelist);
int  	addNodeToList(uint8_t NodeID, NODELIST_t* nodelist);
int 	removeNodeFromList(uint8_t NodeID,NODELIST_t* list);
int 	removeGroupFromList(uint8_t GroupID,GROUPLIST_t* list);
int  	removePopGroupFromList(GROUPLIST_t* list);
int 	removePopNodeFromList(NODELIST_t* list);
int 	removeAllGroupFromList(GROUPLIST_t* list);
int 	removeAllNodeFromList(NODELIST_t* list);
void 	printGroupInList(GROUPLIST_t* list);
void 	printNodeInList(NODELIST_t* list);
int 	addNodeToGroup(uint8_t NodeID,uint8_t GroupID,GROUPLIST_t* list);
int 	removeNodeFromGroup(uint8_t NodeID, uint8_t GroupID, GROUPLIST_t* list);
int 	extractNodesFromList(NODELIST_t* list,uint8_t* buffer,uint8_t* buffer_len);
int  	extractNodesFromGroup(uint8_t GroupID,GROUPLIST_t* list, uint8_t* buffer,uint8_t* buffer_len);
int  	extractGroupsFromList(GROUPLIST_t* list, uint8_t* buffer,uint8_t* buffer_len);





















