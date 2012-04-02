/* 
 * File:   TaskLists.h
 * Author: stephan
 *
 * Created on March 31, 2012, 1:40 PM
 */

#ifndef TASKLISTS_H
#define	TASKLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

/*#ifdef	__cplusplus
extern "C" {
#endif*/
#define TASKLISTS_STRING "tasks#taskLists"
#define KIND_STRING "kind"
#define ETAG_STRING "etag"
#define NEXTPAGETOKEN_STRING "nextPageToken"

typedef struct
{
    char *kind;     /*Type of the resource. This is always "tasks#taskList".*/
    char *id;       /*Task list identifier.*/
    char *etag;     /*ETag of the resource.*/
    char *title;    /*Title of the task list.*/
    char *updated;  /*URL pointing to this task list. Used to retrieve, update, or delete this task list.*/
    char *selfLink; /*Last modification time of the task list (as a RFC 3339 timestamp).*/
}TaskLists;

typedef struct
{
    char *kind;                 /*Type of the resource. This is always "tasks#taskLists".*/
    char *etag;                 /*ETag of the resource.*/
    char *nextPageToken;        /*Token that can be used to request the next page of this result.*/
    int numberItems;
    TaskLists *items;   /*Collection of task lists.*/
}TaskLists_Lists;

/*const char * tasklistidenti = "tasks#taskLists";
const char * erroro = "error";*/

TaskLists_Lists* createNewTaskLists_ListsFromJson(char *jsonResponse);
TaskLists* createNewItem(char *jsonResponse);

void addItemToTaskLists_Lists(TaskLists_Lists *taskLists_Lists, TaskLists *item);
void deleteItemFromTaskLists_list(TaskLists_Lists *taskLists_Lists, char *item);




/*#ifdef	__cplusplus
}
#endif*/

#endif	/* TASKLISTS_H */

