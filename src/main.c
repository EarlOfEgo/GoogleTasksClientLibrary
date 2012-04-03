/* 
 * File:   main.c
 * Author: stephan
 *
 * Created on March 31, 2012, 1:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


#include "TaskLists.h"
#include "json.h"
#include "TaskTasks.h"

/*
char *valid_json_task_list = "{                 \
        \"kind\": \"tasks#tasks\",              \
        \"etag\": \"etag_string\",               \
        \"items\": [\
                {                           \
                \"kind\": \"tasks#task\",       \
                \"id\": \"1\",                  \
                \"etag\": \"etag1_string\",      \
                \"title\": \"task_1_1\",                \
                \"updated\": \"2012-03-28T07:52:57.000Z\",      \
                \"selfLink\": \"https:1\",               \
                \"position\": \"1_1\",  \
                \"status\": \"needsAction\"     \
                },      \
                {       \
                \"kind\": \"tasks#task\",       \
                \"id\": \"2\",  \
                \"etag\": \"etag2_string\",     \
                \"title\": \"task_1_2\",        \
                \"updated\": \"2012-03-30T07:53:43.000Z\",      \
                \"selfLink\": \"https:2\",       \
                \"position\": \"1_2\",  \
                \"status\": \"completed\",      \
                \"completed\": \"2012-03-30T07:53:43.000Z\"     \
                } \
           ]    \
        }";
*/

void printList(TaskLists_Lists *lists)
{
    int i;
    for(i = 0; i < lists->numberItems; i++)
    {
        printf("%s\n", lists->items[i].id);
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
/*
    TaskList* list = createNewTaskListFromJson(valid_json_task_list);
    printf("%s\n", list != NULL ? list->kind : "OH");
*/
 
    
    return (EXIT_SUCCESS);
}

