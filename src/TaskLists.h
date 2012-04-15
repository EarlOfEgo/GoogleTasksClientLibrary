/*
* Copyright (c) 2012 Stephan Hagios <stephan.hagios@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Library General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#ifndef TASKLISTS_H
#define	TASKLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define TASKLISTS_STRING "tasks#taskLists"
#define KIND_STRING "kind"
#define ETAG_STRING "etag"
#define NEXTPAGETOKEN_STRING "nextPageToken"
#define TASKLISTITEM_STRING "tasks#taskList"
#define ID_STRING "id"
#define TITLE_STRING "title"
#define UPDATED_STRING "updated"
#define SELFLINK_STRING "selfLink"

typedef struct
{
    char *kind;     /*Type of the resource. This is always "tasks#taskList".*/ //TODO: Is this realy needed?
    char *id;       /*Task list identifier.*/
    char *etag;     /*ETag of the resource.*/
    char *title;    /*Title of the task list.*/
    char *updated;  /*URL pointing to this task list. Used to retrieve, update, or delete this task list.*/
    char *selfLink; /*Last modification time of the task list (as a RFC 3339 timestamp).*/
}TaskListItem;

typedef struct
{
    char *kind;                 /*Type of the resource. This is always "tasks#taskLists".*/
    char *etag;                 /*ETag of the resource.*/
    char *nextPageToken;        /*Token that can be used to request the next page of this result.*/
    int numberItems;
    TaskListItem *items;   /*Collection of task lists.*/
}TaskLists_Lists;


TaskLists_Lists* createNewTaskLists_ListsFromJson(char *jsonResponse);
TaskListItem* createNewTaskListItem(json_value * value);

void addItemToTaskLists_Lists(TaskLists_Lists *taskLists_Lists, TaskListItem *item);
void deleteItemFromTaskLists_list(TaskLists_Lists *taskLists_Lists, char *item);




#ifdef	__cplusplus
}
#endif

#endif	/* TASKLISTS_H */

