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
#include "helpers.h"

void addItemToTaskLists_Lists(TaskLists_Lists *taskLists_Lists, TaskListItem *item)
{
    void *tmp;
    if (taskLists_Lists->numberItems != 0)
    {
        tmp = realloc(taskLists_Lists->items, ((taskLists_Lists->numberItems + 1) * sizeof (TaskListItem)));
        if (!tmp)
        {
            printf("ERROR, reallocating");
            return;
        }
    } else
    {
        tmp = malloc(sizeof (TaskListItem));
        if (!tmp)
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
    TaskLists_Lists *newList = malloc(sizeof (TaskLists_Lists));
    newList->numberItems = 0;

    for (i = 0; i < taskLists_Lists->numberItems; i++)
    {
        if (taskLists_Lists->items[i].id != NULL)
        {
            if (strcmp(taskLists_Lists->items[i].id, id) == 0)
            {
                indexId = i;
                break;
            } else
                addItemToTaskLists_Lists(newList, &taskLists_Lists->items[i]);
        }
    }

    if (indexId == -1)
        return;

    for (i = (indexId + 1); i < taskLists_Lists->numberItems; i++)
    {
        addItemToTaskLists_Lists(newList, &taskLists_Lists->items[i]);
    }
    taskLists_Lists->items = newList->items;
    taskLists_Lists->numberItems = newList->numberItems;
}

TaskLists_Lists* createNewTaskLists_ListsFromJson(json_value *value)
{

    if (value != NULL)
    {
        TaskLists_Lists *newList = malloc(sizeof (TaskLists_Lists));
        int i, j;
        for (i = 0; i < value->u.object.length; i++)
        {
            if (strcmp(value->u.object.values[i].name, KIND_STRING) == 0)
            {
                newList->kind = malloc(sizeof (TASKLISTS_STRING));
                strcpy(newList->kind, TASKLISTS_STRING);
            } else if (strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
            {
                newList->etag = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(newList->etag, value->u.object.values[i].value->u.string.ptr);
            } else if (strcmp(value->u.object.values[i].name, NEXTPAGETOKEN_STRING) == 0)
            {
                newList->nextPageToken = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(newList->nextPageToken, value->u.object.values[i].value->u.string.ptr);
            } else if (value->u.object.values[i].value->type == json_array)
                for (j = 0; j < value->u.object.values[i].value->u.array.length; j++)
                    addItemToTaskLists_Lists(newList, createNewTaskListItem(value->u.object.values[i].value->u.array.values[j]));
        }
        return newList;
    }
    return NULL;
}

TaskListItem* createNewTaskListItem(json_value * value)
{
    if (value != NULL)
    {
        int i;
        TaskListItem *item = malloc(sizeof (TaskListItem));
        for (i = 0; i < value->u.object.length; i++)
        {
            if (strcmp(value->u.object.values[i].name, KIND_STRING) == 0)
            {
                item->kind = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(item->kind, value->u.object.values[i].value->u.string.ptr);
            } else if (strcmp(value->u.object.values[i].name, ID_STRING) == 0)
            {
                item->id = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(item->id, value->u.object.values[i].value->u.string.ptr);
            } else if (strcmp(value->u.object.values[i].name, ETAG_STRING) == 0)
            {
                item->etag = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(item->etag, value->u.object.values[i].value->u.string.ptr);
            } else if (strcmp(value->u.object.values[i].name, TITLE_STRING) == 0)
            {
                item->title = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(item->title, value->u.object.values[i].value->u.string.ptr);
            } else if (strcmp(value->u.object.values[i].name, SELFLINK_STRING) == 0)
            {
                item->selfLink = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(item->selfLink, value->u.object.values[i].value->u.string.ptr);
            } else if (strcmp(value->u.object.values[i].name, UPDATED_STRING) == 0)
            {
                item->updated = malloc(value->u.object.values[i].value->u.string.length + 1);
                strcpy(item->updated, value->u.object.values[i].value->u.string.ptr);
            }
        }
        return item;
    }
    return NULL;
}

/**
 * Makes this request: GET https://www.googleapis.com/tasks/v1/users/@me/lists
 * @param value
 * @return 
 */
char *taskLists_List(char *access_token, int maxResults /*default = -1*/, char *pageToken, char *fields)
{
    if (access_token != NULL)
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
        str_lenght = strlen(LISTS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, LISTS_HTTP_REQUEST);
        strcat(listsHttpRequest, "?");

        if (maxResults != -1)
        {

            str_lenght += strlen(MAX_RESULTS_STRING);
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, MAX_RESULTS_STRING);
            char buffer [33];

            str_lenght += sprintf(buffer, "%d", maxResults) + 1;
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, buffer);
            strcat(listsHttpRequest, "&");

        }

        if (pageToken != NULL)
        {
            str_lenght += strlen(PAGE_TOKEN_STRING);
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, PAGE_TOKEN_STRING);

            str_lenght += strlen(pageToken) + 1;
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, pageToken);
            strcat(listsHttpRequest, "&");
        }

        if (fields != NULL)
        {
            str_lenght += strlen(FIELDS_STRING);
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, FIELDS_STRING);

            str_lenght += strlen(fields) + 1;
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, fields);
        }

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

/**
 * Makes this request: GET https://www.googleapis.com/tasks/v1/users/@me/lists/taskListsId
 * @param value
 * @return 
 */
char *taskLists_Get(char *access_token, char *taskListsId, char *fields)
{
    if (access_token != NULL)
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

        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *response = NULL;
        str_lenght = strlen(LISTS_HTTP_REQUEST) + 2;
        char *listsHttpRequest = malloc(str_lenght * sizeof (char));
        strcpy(listsHttpRequest, LISTS_HTTP_REQUEST);
        strcat(listsHttpRequest, "/");

        str_lenght += strlen(taskListsId) + 1;
        listsHttpRequest = realloc(listsHttpRequest, str_lenght);
        strcat(listsHttpRequest, taskListsId);
        strcat(listsHttpRequest, "?");

        if (fields != NULL)
        {
            str_lenght += strlen(FIELDS_STRING);
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, FIELDS_STRING);

            str_lenght += strlen(fields) + 1;
            listsHttpRequest = realloc(listsHttpRequest, str_lenght);
            strcat(listsHttpRequest, fields);
        }

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

char *buildPostFields(TaskListItem *item)
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

        if (item->updated != NULL)
        {
            if (added++ > 0)
                str_length = addComma(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(UPDATED_STRING);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, UPDATED_STRING);
            str_length = addQuotes(ret_value);
            str_length = addColon(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(item->updated);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, item->updated);
            str_length = addQuotes(ret_value);
        }

        if (item->selfLink != NULL)
        {
            if (added++ > 0)
                str_length = addComma(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(SELFLINK_STRING);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, SELFLINK_STRING);
            str_length = addQuotes(ret_value);
            str_length = addColon(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(item->selfLink);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, item->selfLink);
            str_length = addQuotes(ret_value);
        }

        if (item->etag != NULL)
        {
            if (added++ > 0)
                str_length = addComma(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(ETAG_STRING);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, ETAG_STRING);
            str_length = addQuotes(ret_value);
            str_length = addColon(ret_value);
            str_length = addQuotes(ret_value);
            str_length += strlen(item->etag);
            ret_value = realloc(ret_value, str_length);
            strcat(ret_value, item->etag);
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

char *taskLists_Insert(char *access_token, TaskListItem *item)
{
    if (access_token != NULL && item != NULL)
    {
        CURL *curl;

        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1);
        memoryStruct.size = 0;

        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);

        str_lenght += appendString(header, access_token);


        headers = curl_slist_append(headers, header);
        headers = curl_slist_append(headers, "Content-Type:  application/json");
        char *postfields = buildPostFields(item);


        struct WriteThis writeThis;
        writeThis.readptr = postfields;
        writeThis.sizeleft = strlen(postfields);


        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        curl_easy_setopt(curl, CURLOPT_URL, LISTS_HTTP_REQUEST);
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
};

char *taskLists_Update(char *access_token, TaskListItem *item)
{
    if (access_token != NULL && item != NULL)
    {
        if (item->id == NULL)
            return NULL;

        CURL *curl;

        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1);
        memoryStruct.size = 0;

        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);



        str_lenght += appendString(header, access_token);


        headers = curl_slist_append(headers, header);
        headers = curl_slist_append(headers, "Content-Type:  application/json");
        char *postfields = buildPostFields(item);

        struct WriteThis writeThis;
        writeThis.readptr = postfields;
        writeThis.sizeleft = strlen(postfields);


        curl = curl_easy_init();

        if (!curl)
        {
            printf("ERROR");
            return NULL;
        }

        char *listHttpRequest = malloc(sizeof (char*));
        appendString(listHttpRequest, LISTS_HTTP_REQUEST);
        appendString(listHttpRequest, "/");
        appendString(listHttpRequest, item->id);


        curl_easy_setopt(curl, CURLOPT_URL, listHttpRequest);
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
}

//DOESN'T WORK RIGHT NOW--> I HAVE NO IDEA WHY...

char *taskLists_Delete(char *access_token, TaskListItem *item)
{

    if (access_token != NULL && item != NULL)
    {
        if (item->id == NULL)
            return NULL;

        CURL *curl;
        
        curl = curl_easy_init();

        struct MemoryStruct memoryStruct;

        memoryStruct.memory = malloc(1);
        memoryStruct.size = 0;

        struct curl_slist *headers = NULL;

        int str_lenght = strlen(HEADER_AUTHORIZATION) + 1;
        char *header = malloc(str_lenght * sizeof (char));
        strcpy(header, HEADER_AUTHORIZATION);

        str_lenght += appendString(header, access_token);


        headers = curl_slist_append(headers, header);

        char *listHttpRequest = malloc(sizeof (char*));
        appendString(listHttpRequest, LISTS_HTTP_REQUEST);
        appendString(listHttpRequest, "/");
        appendString(listHttpRequest, item->id);

        char * postFields = "";
        struct WriteThis writeThis;
        writeThis.readptr = postFields;
        writeThis.sizeleft = strlen(postFields);


        curl_easy_setopt(curl, CURLOPT_URL, listHttpRequest);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &writeThis);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t) writeThis.sizeleft);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30000 / 1000);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return NULL; //memoryStruct.memory;
    }
}