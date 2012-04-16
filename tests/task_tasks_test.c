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

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

char cCurrentPath[FILENAME_MAX];

char *getFileContentForTest(char *path, int *errorCode)
{
    size_t length;
    size_t bytesToRead;
    char* content;
    FILE* f;

    f = fopen(path, "rb");
    if (f == NULL)
    {
        *errorCode = CUE_FOPEN_FAILED;
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    rewind(f);

    content = malloc(sizeof (char) * length + 1);
    content[length] = '\0';
    if (content == NULL)
    {
        *errorCode = CUE_NOMEMORY;
        return NULL;
    }

    bytesToRead = fread(content, sizeof (char), length, f);
    fclose(f);

    return content;
}

char *getFullFileNameForTest(char *fileName)
{
    char *fullFileName = malloc(strlen(&cCurrentPath) + strlen(fileName) + 1);
    strcpy(fullFileName, &cCurrentPath);
    strcat(fullFileName, fileName);
    return fullFileName;
}

/*
 * CUnit Test Suite
 */

int init_suite(void)
{
    if (!GetCurrentDir(cCurrentPath, sizeof (cCurrentPath) / sizeof (char)))
    {
        return CUE_BAD_FILENAME;
    }
    strcat(cCurrentPath, "/tests/jsons/");
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void testAddLinkToTaskItem()
{
    TaskItem* item = malloc(sizeof (TaskItem));
    item->numberLinks = 0;

    int i;
    for (i = 0; i < 26; i++)
    {
        TaskLink* link = malloc(sizeof (TaskLink));
        CU_ASSERT_PTR_NOT_NULL_FATAL(link);
        link->type = (char *) malloc(2);
        link->type[0] = (char) i + 64;
        link->type[1] = '\0';
        addLinkToTaskItem(item, link);

        CU_ASSERT_EQUAL(item->numberLinks, i + 1);
        CU_ASSERT_PTR_NOT_NULL(&item->links[i]);
        CU_ASSERT_STRING_EQUAL(item->links[i].type, link->type);
        CU_ASSERT_PTR_EQUAL(item->links[i].type, link->type);
    }
    free(item);
}

void testAddTaskItemToTaskList()
{
    TaskList* list = malloc(sizeof (TaskList));
    list->numberItems = 0;
    int i = 1;
    for (i = 0; i < 26; i++)
    {
        TaskItem* item = malloc(sizeof (TaskItem));
        CU_ASSERT_PTR_NOT_NULL_FATAL(item);
        item->id = (char *) malloc(2);
        item->id[0] = (char) i + 64;
        item->id[1] = '\0';

        addTaskItemToTaskList(list, item);

        CU_ASSERT_EQUAL(list->numberItems, i + 1);
        CU_ASSERT_PTR_NOT_NULL(&list->items[i]);
        CU_ASSERT_STRING_EQUAL(list->items[i].id, item->id);
        CU_ASSERT_PTR_EQUAL(list->items[i].id, item->id);
    }
}

void testCreateNewTaskItem()
{
    
    char *jsonFullPath = getFullFileNameForTest("taskTaskItem_valid.json");

    int errorCode = 0;
    char *fileContent = getFileContentForTest(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    
    TaskItem* result = createNewTaskItem(value);
    
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_EQUAL(result->numberLinks, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(&result->links[0]);
}

void testCreateNewTaskLinks()
{
    char *jsonFullPath = getFullFileNameForTest("taskTaskLinks_valid.json");

    int errorCode = 0;
    char *fileContent = getFileContentForTest(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    TaskLink* result = createNewTaskLinks(value);
    
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result->description, "description_string");
    CU_ASSERT_STRING_EQUAL(result->link, "link_string");
    CU_ASSERT_STRING_EQUAL(result->type, "type_string");
}

void testCreateNewTaskListFromJson()
{
    char *jsonFullPath = getFullFileNameForTest("taskTaskList_valid.json");

    int errorCode = 0;
    char *fileContent = getFileContentForTest(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    
    TaskList* result = createNewTaskList(value);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_EQUAL(result->numberItems, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(&result->items[0]);
    CU_ASSERT_EQUAL(result->items[0].numberLinks, 1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].links);
}

void testDeleteLinkFromTaskItem()
{
    TaskItem* item = malloc(sizeof (TaskItem));
    item->numberLinks = 0;
     int i;
    for (i = 0; i < 27; i++)
    {
        TaskLink* link = malloc(sizeof (TaskLink));
        CU_ASSERT_PTR_NOT_NULL_FATAL(link);
        link->description = (char *) malloc(2);
        link->description[0] = (char) i + 64;
        link->description[1] = '\0';
        addLinkToTaskItem(item, link);

        CU_ASSERT_EQUAL(item->numberLinks, i + 1);
        CU_ASSERT_PTR_NOT_NULL(&item->links[i]);
        CU_ASSERT_STRING_EQUAL(item->links[i].description, link->description);
        CU_ASSERT_PTR_EQUAL(item->links[i].description, link->description);
    };
    for(i = 0; i < 27; i++)
    {
        char* id = (char *) malloc(2);
        id[0] = (char) i + 64;
        id[1] = '\0';
        CU_ASSERT_EQUAL(item->numberLinks, 27 - i);
        deleteLinkFromTaskItem(item, id);
        CU_ASSERT_EQUAL(item->numberLinks, 26 - i);
        free(id);      
    }
}

void testDeleteTaskItemFromTaskList()
{
    TaskList* list = malloc(sizeof (TaskList));
    list->numberItems = 0;
    int i = 1;
    for (i = 0; i < 27; i++)
    {
        TaskItem* item = malloc(sizeof (TaskItem));
        CU_ASSERT_PTR_NOT_NULL_FATAL(item);
        item->id = (char *) malloc(2);
        item->id[0] = (char) i + 64;
        item->id[1] = '\0';

        addTaskItemToTaskList(list, item);

        CU_ASSERT_EQUAL(list->numberItems, i + 1);
        CU_ASSERT_PTR_NOT_NULL(&list->items[i]);
        CU_ASSERT_STRING_EQUAL(list->items[i].id, item->id);
        CU_ASSERT_PTR_EQUAL(list->items[i].id, item->id);
    }
    
    for(i = 0; i < 27; i++)
    {
        char* id = (char *) malloc(2);
        id[0] = (char) i + 64;
        id[1] = '\0';
        CU_ASSERT_EQUAL(list->numberItems, 27 - i);
        deleteTaskItemFromTaskList(list, id);
        CU_ASSERT_EQUAL(list->numberItems, 26 - i);
        free(id);      
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
