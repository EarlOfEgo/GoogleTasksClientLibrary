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
#include "src/TaskTasks.h"

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

void testAddLinkToTaskItem()
{
    TaskItem* item;
    TaskLink* link;
    addLinkToTaskItem(item, link);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testAddTaskItemToTaskList()
{
    TaskList* list;
    TaskItem* item;
    addTaskItemToTaskList(list, item);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testCreateNewTaskItem()
{
    json_value* value;
    TaskItem* result = createNewTaskItem(value);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testCreateNewTaskLinks()
{
    json_value* value;
    TaskLink* result = createNewTaskLinks(value);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testCreateNewTaskListFromJson()
{
    char* json;
    TaskList* result = createNewTaskListFromJson(json);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testDeleteLinkFromTaskItem()
{
    TaskItem* item;
    char* description;
    deleteLinkFromTaskItem(item, description);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void testDeleteTaskItemFromTaskList()
{
    TaskList* list;
    char* id;
    deleteTaskItemFromTaskList(list, id);
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
    pSuite = CU_add_suite("task_tasks_test", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testAddLinkToTaskItem", testAddLinkToTaskItem)) ||
            (NULL == CU_add_test(pSuite, "testAddTaskItemToTaskList", testAddTaskItemToTaskList)) ||
            (NULL == CU_add_test(pSuite, "testCreateNewTaskItem", testCreateNewTaskItem)) ||
            (NULL == CU_add_test(pSuite, "testCreateNewTaskLinks", testCreateNewTaskLinks)) ||
            (NULL == CU_add_test(pSuite, "testCreateNewTaskListFromJson", testCreateNewTaskListFromJson)) ||
            (NULL == CU_add_test(pSuite, "testDeleteLinkFromTaskItem", testDeleteLinkFromTaskItem)) ||
            (NULL == CU_add_test(pSuite, "testDeleteTaskItemFromTaskList", testDeleteTaskItemFromTaskList)))
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
