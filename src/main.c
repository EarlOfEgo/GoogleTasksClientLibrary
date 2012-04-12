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
#include "googleOauth2Access.h"

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
                \"completed\": \"2012-03-30T07:53:43.000Z\",     \
                \"links\": [    \
                {      \
                        \"type\": \"link_2_type\",     \
                        \"description\": \"link_2_description\",  \
                        \"link\": \"link_2_link\"  \
                }   \
                ]     \
                } \
           ]    \
        }";


/*
 * 
 */
int main(int argc, char** argv) {
 
/*
    TaskList *taskList = createNewTaskListFromJson(valid_json_task_list);
    printf("%s\n", taskList->kind);
    int i;
    for(i = 0; i < taskList->numberItems; i++)
    {
        printf("%s\n", taskList->items[i].id);
        if(taskList->items[i].numberLinks > 0)
            printf("%s\n", taskList->items[i].links[0].description);
    }
*/
    
    printf("%s\n\n", buildAccessTokenRequest());
    char *token = "";
    char *args = buildPostFields(token);

    printf("%s\n",validateAccessToken(args));
    return (EXIT_SUCCESS);
}

