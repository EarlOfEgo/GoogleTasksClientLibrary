#include "TaskTasks.h"

TaskLink* createNewTaskLinks(json_value *value)
{
    TaskLink *link = malloc(sizeof(TaskLink));
    int i;

    for(i = 0; i < value->u.object.length; i++)
    {

        if(strcmp(value->u.object.values[i].name, TYPE_STRING) == 0)
        {
            link->type = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(link->type, value->u.object.values[i].value->u.string.ptr);
        }
        else if(strcmp(value->u.object.values[i].name, DESCRIPTION_STRING) == 0)
        {
            link->description = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(link->description, value->u.object.values[i].value->u.string.ptr); 
        }
        else if(strcmp(value->u.object.values[i].name, LINK_STRING) == 0)
        {
            link->link = malloc(value->u.object.values[i].value->u.string.length);
            strcpy(link->link, value->u.object.values[i].value->u.string.ptr); 
        }


    }
    return link;
}


void addLinkToTaskItem(TaskItem *item, TaskLink *link)
{
    void *tmp;
    if(item->numberLinks != 0)
    {
        tmp = realloc(item->links, ((item->numberLinks + 1) * sizeof(TaskLink)));
        if(!tmp)
        {
            printf("ERROR, reallocating");
            return;
        }
    }
    else
    {
        tmp = malloc(sizeof(TaskLink));
        if(!tmp)
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
    TaskItem *newItem = malloc(sizeof(TaskItem));
    newItem->numberLinks = 0;
    
    for(i = 0; i < item->numberLinks; i++)
    {
        if(item->links[i].description != NULL)
        {
            if(strcmp(item->links[i].description, description) == 0 )
            {
                indexId = i;
                break;
            }
            else
                addLinkToTaskItem(newItem, &item->links[i]);
        }
    }

    if(indexId == -1)
        return;

    for(i = (indexId+1); i < item->numberLinks; i++)
    {
       addLinkToTaskItem(newItem, &item->links[i]);
    }
    item->links = newItem->links;
    item->numberLinks = newItem->numberLinks;
}
