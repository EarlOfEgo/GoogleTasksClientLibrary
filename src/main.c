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
    
    char * data = "{\"kind\":\"tasks#taskLists\",\"etag\": \"string\", \"nextPageToken\": \"string\", \"items\": [ { \"kind\": \"tasks#taskList\", \"id\": \"MDE1ODEyMDkyMDA3MzMwNDQ5OTE6MDow\", \"title\": \"Liste von stephan.hagios\", \"updated\": \"2012-03-28T07:52:57.000Z\", \"selfLink\": \"https://www.googleapis.com/tasks/v1/users/@me/lists/MDE1ODEyMDkyMDA3MzMwNDQ5OTE6MDow\" }, {\"kind\": \"tasks#taskList\", \"id\": \"MDE1ODEyMDkyMDA3MzMwNDQ5OTE6MzQxMzAwOTAxOjA\", \"title\": \"Links\", \"updated\": \"2012-03-30T07:53:42.000Z\", \"selfLink\": \"https://www.googleapis.com/tasks/v1/users/@me/lists/MDE1ODEyMDkyMDA3MzMwNDQ5OTE6MzQxMzAwOTAxOjA\" }] }";
    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value * value = json_parse_ex(&settings, data, error);

    if(value == NULL)
        printf("DRECK");
  else
    {
        printf("%d\n", value->u.object.length);
        int i;
        for(i = 0; i < value->u.object.length; i++)
        {
           
            if(value->u.object.values[i].value->type == json_array)
            {
                int j,k;
                for(j = 0; j < value->u.object.values[i].value->u.array.length; j++)
                    for(k = 0; k < value->u.object.values[i].value->u.array.values[j]->u.object.length; k++)
                        printf("%s\n", value->u.object.values[i].value->u.array.values[j]->u.object.values[k].value->u.string.ptr);
                   
            }
        }
        json_value_free(value);
    }

    return (EXIT_SUCCESS);
}

