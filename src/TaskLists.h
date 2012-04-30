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
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>


#include "json.h"
#include "googleOauth2Access.h"

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




TaskLists_Lists* createNewTaskLists_ListsFromJson(json_value *value);
TaskListItem* createNewTaskListItem(json_value * value);

void addItemToTaskLists_Lists(TaskLists_Lists *taskLists_Lists, TaskListItem *item);
void deleteItemFromTaskLists_list(TaskLists_Lists *taskLists_Lists, char *item);

/* HTTP REQUESTS */
#define LISTS_HTTP_REQUEST "https://www.googleapis.com/tasks/v1/users/@me/lists"
char *taskLists_List(char *access_token, int maxResults, char *pageToken, char *fields);
char *taskLists_Get(char *access_token, char *taskListsId, char *fields);
char *taskLists_Insert(char *access_token, TaskListItem *item);
char *taskLists_Update(char *access_token, TaskListItem *item);
char *taskLists_Delete(char *access_token, TaskListItem *item);

char *buildPostFields(TaskListItem *item);

#define HEADER_AUTHORIZATION "Authorization:  Bearer "

#define MAX_RESULTS_STRING "maxResults="
#define PAGE_TOKEN_STRING "pageToken="
#define FIELDS_STRING "fields="



#ifdef	__cplusplus
}
#endif

#endif	/* TASKLISTS_H */

