/*
 * File:   TaskLists_tests.c
 * Author: stephan
 *
 * Created on Apr 2, 2012, 1:17:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "../src/TaskLists.h"

/*
 * CUnit Test Suite
 */

TaskLists_Lists *lists;

char * json_taskList_valid = "{         \
  \"kind\": \"tasks#taskList\",         \
  \"id\": \"id_string\",                \
  \"etag\": \"etag_string\",            \
  \"title\": \"title_string\",          \
  \"updated\": \"updated_datetime\",    \
  \"selfLink\": \"selfLink_string\"     \
}";

int init_suite_TaskLists(void)
{
    lists = malloc(sizeof(TaskLists_Lists));
    return 0;
}

int clean_suite_TaskLists(void)
{
    free(lists);
    return 0;
}

void test_addAndDeleteAnItemFromTaskLists_list()
{
    
    TaskListItem *item = malloc(sizeof(TaskListItem));
    
    item->id = "1";
    
    addItemToTaskLists_Lists(lists, item);
    
    CU_ASSERT_EQUAL(lists->numberItems, 1);
    CU_ASSERT_PTR_NOT_NULL(item);
    CU_ASSERT_PTR_NOT_NULL(&lists->items[0]);   
//    CU_ASSERT_PTR_EQUAL(&lists->items[0], item);
    
    deleteItemFromTaskLists_list(lists, "2");
    
    CU_ASSERT_EQUAL(lists->numberItems, 1);
    CU_ASSERT_PTR_NOT_NULL(&lists->items[0]);
    
    deleteItemFromTaskLists_list(lists, "1");
    
    CU_ASSERT_EQUAL(lists->numberItems, 0);
    CU_ASSERT_PTR_NULL(&lists->items[0]);
    
    free(item);
}

void test_addAndDeleteMoreItems()
{
    int i;
    for(i = 0; i < 10; i++)
    {
        TaskListItem *item = malloc(sizeof(TaskListItem));
        item->id = (char *)malloc(2);
        item->id[0] = (char) i + 48;
        item->id[1] = '\0';
        addItemToTaskLists_Lists(lists, item);
        CU_ASSERT_EQUAL(lists->numberItems, i+1);
        CU_ASSERT_PTR_NOT_NULL(item);
        CU_ASSERT_PTR_NOT_NULL(&lists->items[i]);
    }
    for(i = 0; i < 10; i++)
    {
        char *id = (char *)malloc(2);
        id[0] = (char) i + 48;
        id[1] = '\0';
        deleteItemFromTaskLists_list(lists, id);
        free(id);
    
        CU_ASSERT_EQUAL(lists->numberItems, (9-i));
    }
    
}

void test_createNewItem()
{
    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value * value = json_parse_ex(&settings, json_taskList_valid, error);
    TaskListItem *item =  createNewTaskListItem(value);
    CU_ASSERT_PTR_NOT_NULL(item);

    CU_ASSERT_STRING_EQUAL(item->kind, "tasks#taskList");
    CU_ASSERT_STRING_EQUAL(item->id, "id_string");
    CU_ASSERT_STRING_EQUAL(item->etag, "etag_string");
    CU_ASSERT_STRING_EQUAL(item->selfLink, "selfLink_string");
    CU_ASSERT_STRING_EQUAL(item->updated, "updated_datetime");
 
}
