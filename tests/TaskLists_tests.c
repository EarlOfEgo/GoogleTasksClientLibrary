/*
 * File:   TaskLists_tests.c
 * Author: stephan
 *
 * Created on Apr 2, 2012, 1:17:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "src/TaskLists.h"

/*
 * CUnit Test Suite
 */

TaskLists_Lists *lists;

int init_suite(void)
{
    lists = malloc(sizeof(TaskLists_Lists));
    return 0;
}

int clean_suite(void)
{
    free(lists);
    return 0;
}

void test_addAndDeleteAnItem()
{
    
    TaskLists *item = malloc(sizeof(TaskLists));
    
    item->id = "1";
    
    addItemToTaskLists_Lists(lists, item);
    
    CU_ASSERT_EQUAL(lists->numberItems, 1);
    CU_ASSERT_PTR_NOT_NULL(item);
    CU_ASSERT_PTR_NOT_NULL(&lists->items[0]);
 //   CU_ASSERT_PTR_EQUAL(&lists->items[0], item);
    
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
        TaskLists *item = malloc(sizeof(TaskLists));
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

int main()
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("TaskLists_tests", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test1", test_addAndDeleteAnItem)) ||
            (NULL == CU_add_test(pSuite, "test2", test_addAndDeleteMoreItems)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
