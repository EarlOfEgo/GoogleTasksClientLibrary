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

typedef struct
{
    char *type;
    char *description;
    char *link;
}TaskLinks;

typedef struct
{
    char *kind;
    char *id;
    char *etag;
    char *title;
    char *updated;
    char *selfLink;
    char *parent;
    char *position;
    char *notes;
    char *status;
    char *due;
    char *completed;
    char *deleted;
    char *hidden;
    int numberLinks;
    TaskLinks *links;
    
}TaskItem;

typedef struct
{
    char *kind;
    char *etag;
    char *nextPageToken;
    int numberItems;
    TaskItem *items;
}TaskTasks;



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TASKTASKS_H */

