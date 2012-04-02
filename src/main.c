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
    
 

    return (EXIT_SUCCESS);
}

