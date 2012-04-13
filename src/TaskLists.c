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

#include "TaskLists.h"

void addItemToTaskLists_Lists(TaskLists_Lists *taskLists_Lists, TaskListItem *item)
{
    void *tmp;
    if(taskLists_Lists->numberItems != 0)
    {
        tmp = realloc(taskLists_Lists->items, ((taskLists_Lists->numberItems + 1) * sizeof(TaskListItem)));
        if(!tmp)
        {
            printf("ERROR, reallocating");
            return;
        }
    }
    else
    {
        tmp = malloc(sizeof(TaskListItem));
        if(!tmp)
        {
            printf("ERROR, allocating");
            return;
        }
    }
    taskLists_Lists->items = (TaskListItem*) tmp;
    taskLists_Lists->items[taskLists_Lists->numberItems++] = *item;
}

void deleteItemFromTaskLists_list(TaskLists_Lists *taskLists_Lists, char *id)
{
    int i;
    int indexId = -1;
    TaskLists_Lists *newList = malloc(sizeof(TaskLists_Lists));
    newList->numberItems = 0;
    
    for(i = 0; i < taskLists_Lists->numberItems; i++)
    {
        if(taskLists_Lists->items[i].id != NULL)
        {
            if(strcmp(taskLists_Lists->items[i].id, id) == 0 )
            {
                indexId = i;
                break;
            }
            else
                addItemToTaskLists_Lists(newList, &taskLists_Lists->items[i]);
        }
    }

    if(indexId == -1)
        return;

    for(i = (indexId+1); i < taskLists_Lists->numberItems; i++)
    {
        addItemToTaskLists_Lists(newList, &taskLists_Lists->items[i]);
    }
    taskLists_Lists->items = newList->items;
    taskLists_Lists->numberItems = newList->numberItems;
}


TaskLists_Lists* createNewTaskLists_ListsFromJson(char *jsonResponse)
{
    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value * value = json_parse_ex(&settings, jsonResponse, error);
    
    if(value != NULL)
    {
        TaskLists_Lists *newList = malloc(sizeof(TaskLists_Lists));
        int i, j;
        for(i = 0; i < value->u.object.length; i++)
        {
           if(strcmp(value->u.object.values[i].name, KIND_STRING) == 0) 
           {
               newList->kind = malloc(sizeof(TASKLISTS_STRING));
               strcpy(newList->kind, TASKLISTS_STRING);
           }
           else if(strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
           {
               newList->etag = malloc(value->u.object.values[i].value->u.string.length);
               strcpy(newList->etag, value->u.object.values[i].value->u.string.ptr);
           }
           else if(strcmp(value->u.object.values[i].name, NEXTPAGETOKEN_STRING) == 0)
           {
               newList->nextPageToken = malloc(value->u.object.values[i].value->u.string.length);
               strcpy(newList->nextPageToken, value->u.object.values[i].value->u.string.ptr);
           }
           else if(value->u.object.values[i].value->type == json_array)
               for(j = 0; j < value->u.object.values[i].value->u.array.length; j++)
                    addItemToTaskLists_Lists(newList, createNewTaskListItem(value->u.object.values[i].value->u.array.values[j]));
        }
        json_value_free(value); 
        return newList;
    }
    return NULL;
}


TaskListItem* createNewTaskListItem(json_value * value)
{
    int i;
    TaskListItem *item = malloc(sizeof(TaskListItem));
    for(i = 0; i < value->u.object.length; i++)
    {
        if(strcmp(value->u.object.values[i].name, KIND_STRING) == 0) 
        {
            item->kind = malloc(sizeof(TASKLISTITEM_STRING));
            strcpy(item->kind, TASKLISTITEM_STRING);
        }
        else if(strcmp(value->u.object.values[i].name, ID_STRING) == 0)
        {
            item->id = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(item->id, value->u.object.values[i].value->u.string.ptr);
        }
        else if(strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
        {
            item->etag = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(item->etag, value->u.object.values[i].value->u.string.ptr);
        }
        else if(strcmp(value->u.object.values[i].name, TITLE_STRING) == 0)
        {
            item->title = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(item->title, value->u.object.values[i].value->u.string.ptr);
        }
        else if(strcmp(value->u.object.values[i].name, SELFLINK_STRING) == 0)
        {
            item->selfLink = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(item->selfLink, value->u.object.values[i].value->u.string.ptr);
        }
        else if(strcmp(value->u.object.values[i].name, UPDATED_STRING) == 0)
        {
            item->updated = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(item->updated, value->u.object.values[i].value->u.string.ptr);
        }
    }
    return item;
}