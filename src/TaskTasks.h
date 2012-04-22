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

#ifndef TASKTASKS_H
#define	TASKTASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "helpers.h"

#define TYPE_STRING "type"
#define DESCRIPTION_STRING "description"
#define LINK_STRING "link"
#define PARENT_STRING "parent"
#define POSITION_STRING "position"
#define NOTES_STRING "notes"
#define STATUS_STRING "status"
#define DUE_STRING "due"
#define COMPLETED_STRING "completed"
#define DELETED_STRING "deleted"
#define HIDDEN_STRING "hidden"


typedef struct
{
    char *type;         /*Type of the link, e.g. "email".*/
    char *description;  /*The description. In HTML speak: Everything between <a> and </a>.*/
    char *link;         /*The URL.*/
}TaskLink;

typedef struct
{
    char *kind;         /*Type of the resource. This is always "tasks#task".*/
    char *id;           /*Task identifier.*/
    char *etag;         /*ETag of the resource.*/
    char *title;        /*Title of the task.*/
    char *updated;      /*Last modification time of the task (as a RFC 3339 timestamp).*/
    char *selfLink;     /*URL pointing to this task. Used to retrieve, update, or delete this task.*/
    char *parent;       /*Parent task identifier. This field is omitted if it is a top-level task. This field is read-only. Use the "move" method to move the task under a different parent or to the top level.*/
    char *position;     /*String indicating the position of the task among its sibling tasks under the same parent task or at the top level. If this string is greater than another task's corresponding position string according to lexicographical ordering, the task is positioned after the other task under the same parent task (or at the top level). This field is read-only. Use the "move" method to move the task to another position.*/
    char *notes;        /*Notes describing the task. Optional.*/
    char *status;       /*Status of the task. This is either "needsAction" or "completed".*/
    char *due;          /*Due date of the task (as a RFC 3339 timestamp). Optional.*/
    char *completed;    /*Completion date of the task (as a RFC 3339 timestamp). This field is omitted if the task has not been completed.*/
    int deleted;      /*Flag indicating whether the task has been deleted. The default if False.*/
    int hidden;       /*Flag indicating whether the task is hidden. This is the case if the task had been marked completed when the task list was last cleared. The default is False. This field is read-only.*/
    int numberLinks;    /*Number of links*/
    TaskLink *links;    /*Collection of links. This collection is read-only.*/
    
}TaskItem;

typedef struct
{
    char *kind;         /*Type of the resource. This is always "tasks#tasks".*/            
    char *etag;         /*ETag of the resource.*/         
    char *nextPageToken;/*Token used to access the next page of this result.*/        
    int numberItems;    /*Number of items*/ 
    TaskItem *items;    /*Collection of tasks.*/
}TaskList;

TaskLink* createNewTaskLinks(json_value *value);

TaskList* createNewTaskList(json_value *value);

void addLinkToTaskItem(TaskItem *item, TaskLink *link);
void deleteLinkFromTaskItem(TaskItem *item, char *description);

void addTaskItemToTaskList(TaskList *list, TaskItem *item);
void deleteTaskItemFromTaskList(TaskList *list, char *id);

TaskItem *createNewTaskItem(json_value *value);

static char *buildPostFieldsTaskItem(TaskItem *item);


char *taskTasks_List(char *access_token, char *taskList);//Others are optional, will be added later..
char *taskTasks_Get(char *access_token, char *taskListsId, char *taskTaskId);
char *taskTasks_Insert(char *access_token, char *taskListsId, TaskItem *item);

#define TASKS_HTTP_REQUEST "https://www.googleapis.com/tasks/v1/lists"


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TASKTASKS_H */

