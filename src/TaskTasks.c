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

#include "TaskTasks.h"
#include "TaskLists.h"

#include "helpers.h"

TaskLink* createNewTaskLinks(json_value *value)
{
    TaskLink *link = malloc(sizeof (TaskLink));
    int i;

    for (i = 0; i < value->u.object.length; i++)
    {

        if (strcmp(value->u.object.values[i].name, TYPE_STRING) == 0)
        {
            link->type = malloc(value->u.object.values[i].value->u.string.length + 1);
            strcpy(link->type, value->u.object.values[i].value->u.string.ptr);
        } else if (strcmp(value->u.object.values[i].name, DESCRIPTION_STRING) == 0)
        {
            link->description = malloc(value->u.object.values[i].value->u.string.length + 1);
            strcpy(link->description, value->u.object.values[i].value->u.string.ptr);
        } else if (strcmp(value->u.object.values[i].name, LINK_STRING) == 0)
        {
            link->link = malloc(value->u.object.values[i].value->u.string.length + 1);
            strcpy(link->link, value->u.object.values[i].value->u.string.ptr);
        }


    }
    return link;
}

void addLinkToTaskItem(TaskItem *item, TaskLink *link)
{
    void *tmp;
    if (item->numberLinks != 0)
    {
        tmp = realloc(item->links, ((item->numberLinks + 1) * sizeof (TaskLink)));
        if (!tmp)
        {
            printf("ERROR, reallocating");
            return;
        }
    } else
    {
        tmp = malloc(sizeof (TaskLink));
        if (!tmp)
        {
            printf("ERROR, allocating");
            return;
        }
    }
    item->links = (TaskLink*) tmp;
    item->links[item->numberLinks++] = *link;
}

void deleteLinkFromTaskItem(TaskItem *item, char *description)
{
    int i;
    int indexId = -1;
    TaskItem *newItem = malloc(sizeof (TaskItem));
    newItem->numberLinks = 0;

    for (i = 0; i < item->numberLinks; i++)
    {
        if (item->links[i].description != NULL)
        {
            if (strcmp(item->links[i].description, description) == 0)
            {
                indexId = i;
                break;
            } else
                addLinkToTaskItem(newItem, &item->links[i]);
        }
    }

    if (indexId == -1)
        return;

    for (i = (indexId + 1); i < item->numberLinks; i++)
    {
        addLinkToTaskItem(newItem, &item->links[i]);
    }
    item->links = newItem->links;
    item->numberLinks = newItem->numberLinks;
}

void addTaskItemToTaskList(TaskList *list, TaskItem *item)
{
    void *tmp;
    if (list->numberItems != 0)
    {
        tmp = realloc(list->items, ((list->numberItems + 1) * sizeof (TaskItem)));
        if (!tmp)
        {
            printf("ERROR, reallocating");
            return;
        }
    } else
    {
        tmp = malloc(sizeof (TaskItem));
        if (!tmp)
        {
            printf("ERROR, allocating");
            return;
        }
    }
    list->items = (TaskItem*) tmp;
    list->items[list->numberItems++] = *item;
}

void deleteTaskItemFromTaskList(TaskList *list, char *id)
{
    int i;
    int indexId = -1;
    TaskList *newList = malloc(sizeof (TaskList));
    newList->numberItems = 0;

    for (i = 0; i < list->numberItems; i++)
    {
        if (list->items[i].id != NULL)
        {
            if (strcmp(list->items[i].id, id) == 0)
            {
                indexId = i;
                break;
            } else
                addTaskItemToTaskList(newList, &list->items[i]);
        }
    }

    if (indexId == -1)
        return;

    for (i = (indexId + 1); i < list->numberItems; i++)
    {
        addTaskItemToTaskList(newList, &list->items[i]);
    }
    list->items = newList->items;
    list->numberItems = newList->numberItems;
}

TaskList* createNewTaskList(json_value *value)
{
    if (value != NULL)
    {
        TaskList* newTaskList = malloc(sizeof (TaskList));
        int i, j;
        for (i = 0; i < value->u.object.length; i++)
        {
            if (value->u.object.values[i].value->type != json_array)
            {
                if (strcmp(value->u.object.values[i].name, KIND_STRING) == 0)
                {
                    newTaskList->kind = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newTaskList->kind, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
                {
                    newTaskList->etag = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newTaskList->etag, value->u.object.values[i].value->u.string.ptr);
                }
            } else
                for (j = 0; j < value->u.object.values[i].value->u.array.length; j++)
                    addTaskItemToTaskList(newTaskList, createNewTaskItem(value->u.object.values[i].value->u.array.values[j]));
        }
        return newTaskList;
    }


    return NULL;
}

TaskItem *createNewTaskItem(json_value *value)
{
    if (value != NULL)
    {
        TaskItem *newItem = malloc(sizeof (TaskItem));
        int i, j;
        for (i = 0; i < value->u.object.length; i++)
        {
            if (value->u.object.values[i].value->type != json_array)
            {
                if (strcmp(value->u.object.values[i].name, KIND_STRING) == 0)
                {
                    newItem->kind = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->kind, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, ID_STRING) == 0)
                {
                    newItem->id = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->id, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
                {
                    newItem->etag = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->etag, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, TITLE_STRING) == 0)
                {
                    newItem->title = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->title, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, UPDATED_STRING) == 0)
                {
                    newItem->updated = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->updated, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
                {
                    newItem->etag = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->etag, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, SELFLINK_STRING) == 0)
                {
                    newItem->selfLink = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->selfLink, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, PARENT_STRING) == 0)
                {
                    newItem->parent = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->parent, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, POSITION_STRING) == 0)
                {
                    newItem->position = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->position, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, NOTES_STRING) == 0)
                {
                    newItem->notes = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->notes, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, STATUS_STRING) == 0)
                {
                    newItem->status = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->status, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, DUE_STRING) == 0)
                {
                    newItem->due = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->due, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, COMPLETED_STRING) == 0)
                {
                    newItem->completed = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(newItem->completed, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, DELETED_STRING) == 0)
                {
                    if (value->u.object.values[i].value->type == json_boolean)
                    {
                        newItem->deleted = value->u.object.values[i].value->u.boolean;
                    }
                    /*
                                        else
                                        {
                                            newItem->deleted = malloc(value->u.object.values[i].value->u.string.length + 1);
                                            strcpy(newItem->deleted, value->u.object.values[i].value->u.string.ptr);
                                        }
                     */

                } else if (strcmp(value->u.object.values[i].name, HIDDEN_STRING) == 0)
                {
                    if (value->u.object.values[i].value->type == json_boolean)
                    {
                        newItem->hidden = value->u.object.values[i].value->u.boolean;
                    }
                    /*
                                        else
                                        {
                                            newItem->hidden = malloc(value->u.object.values[i].value->u.string.length + 1);
                                            strcpy(newItem->hidden, value->u.object.values[i].value->u.string.ptr);
                                        }
                     */
                }
            } else
                for (j = 0; j < value->u.object.values[i].value->u.array.length; j++)
                    addLinkToTaskItem(newItem, createNewTaskLinks(value->u.object.values[i].value->u.array.values[j]));
        }
        return newItem;
    }
    return NULL;
}

char *taskTasks_List(char *access_token, char *taskList)
{
    if (access_token != NULL)
    {
        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1); /* will be grown as needed by the realloc above */
        memoryStruct.size = 0; /* no data at this point */

        CURL *curl;
        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);


        str_lenght += strlen(access_token);
        header = realloc(header, str_lenght);
        strcat(header, access_token);


        headers = curl_slist_append(headers, header);
        if (headers != NULL) printf("\n%s\n", headers->data);

        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *response = NULL;
        str_lenght = strlen(TASKS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, TASKS_HTTP_REQUEST);
        strcat(listsHttpRequest, "/");



        str_lenght += strlen(taskList);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskList);

        str_lenght += strlen("/tasks");
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, "/tasks");

        curl_easy_setopt(curl, CURLOPT_URL, listsHttpRequest);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &memoryStruct);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return memoryStruct.memory;
    }
    return NULL;
}

char *taskTasks_Get(char *access_token, char *taskListsId, char *taskTaskId)
{
    if (access_token != NULL && taskListsId != NULL && taskTaskId != NULL)
    {
        struct MemoryStruct chunk;

        chunk.memory = malloc(1); /* will be grown as needed by the realloc above */
        chunk.size = 0; /* no data at this point */

        CURL *curl;
        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);


        str_lenght += strlen(access_token);
        header = realloc(header, str_lenght);
        strcat(header, access_token);


        headers = curl_slist_append(headers, header);
        if (headers != NULL) printf("\n%s\n", headers->data);

        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *response = NULL;
        str_lenght = strlen(TASKS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, TASKS_HTTP_REQUEST);
        strcat(listsHttpRequest, "/");



        str_lenght += strlen(taskListsId);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskListsId);

        str_lenght += strlen("/tasks/");
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, "/tasks/");

        str_lenght += strlen(taskTaskId);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskTaskId);

        curl_easy_setopt(curl, CURLOPT_URL, listsHttpRequest);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return chunk.memory;
    }
    return NULL;
}

char *taskTasks_Insert(char *access_token, char *taskListsId, TaskItem *item)
{
    if (access_token != NULL && taskListsId != NULL && item != NULL)
    {
        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1);
        memoryStruct.size = 0;

        CURL *curl;
        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);


        str_lenght += strlen(access_token);
        header = realloc(header, str_lenght);
        strcat(header, access_token);


        headers = curl_slist_append(headers, header);
        headers = curl_slist_append(headers, "Content-Type:  application/json");
        if (headers != NULL) printf("\n%s\n", headers->data);

        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *response = NULL;
        str_lenght = strlen(TASKS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, TASKS_HTTP_REQUEST);
        strcat(listsHttpRequest, "/");



        str_lenght += strlen(taskListsId);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskListsId);

        str_lenght += strlen("/tasks");
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, "/tasks");

        char * postFields = buildPostFieldsTaskItem(item);
        struct WriteThis writeThis;
        writeThis.readptr = postFields;
        writeThis.sizeleft = strlen(postFields);


        curl_easy_setopt(curl, CURLOPT_URL, listsHttpRequest);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &writeThis);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t) writeThis.sizeleft);



        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30000 / 1000);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        return memoryStruct.memory;
    }
    return NULL;
}

static char *buildPostFieldsTaskItem(TaskItem *item)//TODO: add all fields
{
    int str_length = strlen("{") + 1;
    char *ret_value = malloc(str_length * sizeof (char));
    strcpy(ret_value, "{");
    int added = 0;
    if (item != NULL)
    {

        if (item->title != NULL)
        {
            str_length = addQuotes(ret_value);
            str_length += strlen(TITLE_STRING);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, TITLE_STRING);
            addQuotes(ret_value);
            addColon(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(item->title);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, item->title);
            str_length = addQuotes(ret_value);
            added++;
        }

        if (item->id != NULL)
        {
            if (added++ > 0)
                str_length = addComma(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(ID_STRING);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, ID_STRING);
            str_length = addQuotes(ret_value);
            str_length = addColon(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(item->id);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, item->id);
            str_length = addQuotes(ret_value);
        }

        if (item->kind != NULL)
        {
            if (added++ > 0)
                str_length = addComma(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(KIND_STRING);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, KIND_STRING);
            str_length = addQuotes(ret_value);
            str_length = addColon(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(item->kind);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, item->kind);
            str_length = addQuotes(ret_value);
        }
    }

    appendString(ret_value, "}");
    return ret_value;
}


char *taskTasks_Update(char *access_token, char *taskListsId, TaskItem *item)
{
    if (access_token != NULL && taskListsId != NULL && item != NULL)
    {
        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1);
        memoryStruct.size = 0;

        CURL *curl;
        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);


        str_lenght += strlen(access_token);
        header = realloc(header, str_lenght);
        strcat(header, access_token);


        headers = curl_slist_append(headers, header);
        headers = curl_slist_append(headers, "Content-Type:  application/json");

        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *response = NULL;
        str_lenght = strlen(TASKS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, TASKS_HTTP_REQUEST);
        strcat(listsHttpRequest, "/");



        str_lenght += strlen(taskListsId);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskListsId);

        str_lenght += strlen("/tasks/");
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, "/tasks/");
        
        str_lenght += strlen(item->id);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, item->id);
        printf("%s\n", listsHttpRequest);
        

        char * postFields = buildPostFieldsTaskItem(item);
        printf("%s\n", postFields);
        
        struct WriteThis writeThis;
        writeThis.readptr = postFields;
        writeThis.sizeleft = strlen(postFields);


        curl_easy_setopt(curl, CURLOPT_URL, listsHttpRequest);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_PUT, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &writeThis);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t) writeThis.sizeleft);



        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30000 / 1000);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        return memoryStruct.memory;
    }
    return NULL;
}


char *taskTasks_Clear(char* access_token, char * taskListId)
{
    if (access_token != NULL && taskListId != NULL)
    {
        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1);
        memoryStruct.size = 0;

        CURL *curl;
        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);


        str_lenght += strlen(access_token);
        header = realloc(header, str_lenght);
        strcat(header, access_token);


        headers = curl_slist_append(headers, header);
        if (headers != NULL) printf("\n%s\n", headers->data);

        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *response = NULL;
        str_lenght = strlen(TASKS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, TASKS_HTTP_REQUEST);
        strcat(listsHttpRequest, "/");



        str_lenght += strlen(taskListId);
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskListId);

        str_lenght += strlen("/clear");
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, "/clear");
 

        char * postFields = "";
        struct WriteThis writeThis;
        writeThis.readptr = postFields;
        writeThis.sizeleft = strlen(postFields);


        curl_easy_setopt(curl, CURLOPT_URL, listsHttpRequest);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &writeThis);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t) writeThis.sizeleft);



        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30000 / 1000);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        return memoryStruct.memory;
    }
    return NULL;
}
