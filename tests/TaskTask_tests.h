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





int init_suite_TaskTasks(void)
{
    return 0;
}

int clean_suite_TaskTasks(void)
{ 
    return 0;
}

void test_createTaskLink(void)
{
    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
//    json_value * value = json_parse_ex(&settings, valid_json_task_links, error);
    json_value *value= json_parse(valid_json_task_links);
    TaskLink *link = createNewTaskLinks(value);
    CU_ASSERT_PTR_NOT_NULL(link);
    if(link != NULL)
    {
        CU_ASSERT_STRING_EQUAL(link->description, "description_string");
        CU_ASSERT_STRING_EQUAL(link->link, "link_string");
        CU_ASSERT_STRING_EQUAL(link->type, "type_string"); 
    }
  //  json_value_free(value);
    free(link);
}

void test_addAndDeleteALink()
{
    
    TaskLink *link = malloc(sizeof(TaskLink));
    
    link->description = "1";
    TaskItem *item = malloc(sizeof(TaskItem));
    item->numberLinks = 0;
    
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


void test_addAndDeleteAnItemFromTaskList()
{
    TaskList *tasks = malloc(sizeof(TaskList));
    tasks->numberItems = 0;
    TaskItem *item = malloc(sizeof(TaskItem));
    item->id = "1";
    
    addTaskItemToTaskList(tasks, item);
    CU_ASSERT_EQUAL(tasks->numberItems, 1);
    CU_ASSERT_PTR_NOT_NULL(&tasks->items[0]); 

    deleteTaskItemFromTaskList(tasks, "2");
    CU_ASSERT_EQUAL(tasks->numberItems, 1);
    CU_ASSERT_PTR_NOT_NULL(tasks);
    CU_ASSERT_PTR_NOT_NULL(&tasks->items[0]);
    
    deleteTaskItemFromTaskList(tasks, "1");
    CU_ASSERT_EQUAL(tasks->numberItems, 0);
    CU_ASSERT_PTR_NOT_NULL(tasks);
    CU_ASSERT_PTR_NULL(&tasks->items[0]);

    free(tasks);
}


void test_createNewTaskListFromJson()
{
    TaskList *list = malloc(sizeof(TaskList));
    list = createNewTaskListFromJson(valid_json_task_list);
    printf("%s!!\n", list->kind);
    CU_ASSERT_PTR_NOT_NULL(list);
}
