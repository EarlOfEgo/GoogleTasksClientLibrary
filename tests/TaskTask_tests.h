/* 
 * File:   TaskTask_tests.c
 * Author: stephan
 * 
 * Created on April 2, 2012, 5:31 PM
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "../src/TaskTasks.h"

char *valid_json_task_links = "{                \
      \"type\": \"type_string\",                    \
      \"description\": \"description_string\",      \
      \"link\": \"link_string\"                     \
    }";

TaskTasks *tasks;
TaskItem *item;

int init_suite_TaskTasks(void)
{
    tasks = malloc(sizeof(TaskTasks));
    item = malloc(sizeof(TaskItem));
    return 0;
}

int clean_suite_TaskTasks(void)
{
    free(tasks);
    free(item);
    return 0;
}

void test_createTaskLink(void)
{
    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value * value = json_parse_ex(&settings, valid_json_task_links, error);
    TaskLink *link = createNewTaskLinks(value);
    CU_ASSERT_PTR_NOT_NULL(link);
//    if(link != NULL)
    {
//        CU_ASSERT_STRING_EQUAL(link->description, "description_string");
//        CU_ASSERT_STRING_EQUAL(link->link, "link_string");
//        CU_ASSERT_STRING_EQUAL(link->type, "type_string"); 
    }
    
}

void test_addAndDeleteAnLink()
{
    
    TaskLink *link = malloc(sizeof(TaskLink));
    
    link->description = "1";
    
    addLinkToTaskItem(item, link);
    
    CU_ASSERT_EQUAL(item->numberLinks, 1);
    CU_ASSERT_PTR_NOT_NULL(item);
    CU_ASSERT_PTR_NOT_NULL(&item->links[0]);   
//    CU_ASSERT_PTR_EQUAL(&lists->items[0], item);

    deleteLinkFromTaskItem(item, "2");
    CU_ASSERT_EQUAL(item->numberLinks, 1);
    CU_ASSERT_PTR_NOT_NULL(item);
    CU_ASSERT_PTR_NOT_NULL(&item->links[0]);
    
    deleteLinkFromTaskItem(item, "1");
    CU_ASSERT_EQUAL(item->numberLinks, 0);
    CU_ASSERT_PTR_NOT_NULL(item);
    CU_ASSERT_PTR_NULL(&item->links[0]);
    
    free(link);
}



