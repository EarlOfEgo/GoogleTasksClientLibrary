/* 
 * File:   TaskTask_tests.c
 * Author: stephan
 * 
 * Created on April 2, 2012, 5:31 PM
 */


/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: testFPRINTF ... passed
 *         Test: testFREAD ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "TaskLists_tests.h"
#include "TaskTask_tests.h"

void runSuite1()
{
    CU_pSuite pSuite_TaskLists = NULL;
    

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite_TaskLists = CU_add_suite("TaskLists_tests", init_suite_TaskLists, clean_suite_TaskLists);
    
    if (pSuite_TaskLists == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((CU_add_test(pSuite_TaskLists, "test_addAndDeleteAnItem", test_addAndDeleteAnItemFromTaskLists_list) == NULL) ||
            (CU_add_test(pSuite_TaskLists, "test_addAndDeleteMoreItems", test_addAndDeleteMoreItems)  == NULL) ||
            (CU_add_test(pSuite_TaskLists, "test_createNewItem", test_createNewItem)  == NULL)
            )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}

void runSuite2()
{
    CU_pSuite pSuite_TaskTasks = NULL;
    pSuite_TaskTasks = CU_add_suite("TaskTasks_tests", init_suite_TaskTasks, clean_suite_TaskTasks);
     if (pSuite_TaskTasks == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
     if ((CU_add_test(pSuite_TaskTasks, "test_createTaskLink", test_createTaskLink)  == NULL) ||
            (CU_add_test(pSuite_TaskTasks, "test_addAndDeleteAnLink", test_addAndDeleteALink)  == NULL) ||
            (CU_add_test(pSuite_TaskTasks, "test_addAndDeleteAnItemFromTaskList", test_addAndDeleteAnItemFromTaskList)  == NULL) ||
            (CU_add_test(pSuite_TaskTasks, "test_createNewTaskListFromJson", test_createNewTaskListFromJson)  == NULL)
            )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}




/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
    runSuite1();
    runSuite2();
    
    
    return CU_get_error();
}