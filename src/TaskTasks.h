/* 
 * File:   TaskTasks.h
 * Author: stephan
 *
 * Created on April 2, 2012, 4:50 PM
 */

#ifndef TASKTASKS_H
#define	TASKTASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

#define TYPE_STRING "type"
#define DESCRIPTION_STRING "description"
#define LINK_STRING "link"


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
    char *deleted;      /*Flag indicating whether the task has been deleted. The default if False.*/
    char *hidden;       /*Flag indicating whether the task is hidden. This is the case if the task had been marked completed when the task list was last cleared. The default is False. This field is read-only.*/
    int numberLinks;    /*Number of links*/
    TaskLink *links;   /*Collection of links. This collection is read-only.*/
    
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

void addLinkToTaskItem(TaskItem *item, TaskLink *link);
void deleteLinkFromTaskItem(TaskItem *item, char *description);

void addTaskItemToTaskList(TaskList *list, TaskItem *item);
void deleteTaskItemFromTaskList(TaskList *list, char *id);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TASKTASKS_H */

