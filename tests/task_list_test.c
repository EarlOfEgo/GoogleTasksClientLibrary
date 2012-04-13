/*
* Copyright (c) 2012 Stephan Hagios <stephan.hagios@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Library General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "src/TaskLists.h"

/*
 * CUnit Test Suite
 */

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void testAddItemToTaskLists_Lists()
{
    TaskLists_Lists* taskLists_Lists = malloc(sizeof(TaskLists_Lists));
    TaskListItem* item = malloc(sizeof(TaskListItem));
    addItemToTaskLists_Lists(taskLists_Lists, item);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testCreateNewTaskListItem()
{
    json_value* value;
    TaskListItem* result = createNewTaskListItem(value);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testCreateNewTaskLists_ListsFromJson()
{
    char* jsonResponse;
    TaskLists_Lists* result = createNewTaskLists_ListsFromJson(jsonResponse);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testDeleteItemFromTaskLists_list()
{
    TaskLists_Lists* taskLists_Lists;
    char* item;
    deleteItemFromTaskLists_list(taskLists_Lists, item);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("task_list_test", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testAddItemToTaskLists_Lists", testAddItemToTaskLists_Lists)) ||
            (NULL == CU_add_test(pSuite, "testCreateNewTaskListItem", testCreateNewTaskListItem)) ||
            (NULL == CU_add_test(pSuite, "testCreateNewTaskLists_ListsFromJson", testCreateNewTaskLists_ListsFromJson)) ||
            (NULL == CU_add_test(pSuite, "testDeleteItemFromTaskLists_list", testDeleteItemFromTaskLists_list)))
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
