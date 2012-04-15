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

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "CUnit/Basic.h"
#include "src/TaskLists.h"

char cCurrentPath[FILENAME_MAX];

char *getFileContent(char *path, int *errorCode)
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

char *getFullFileName(char *fileName)
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

void testAddItemToTaskLists_Lists()
{
    TaskLists_Lists* taskLists_Lists = malloc(sizeof (TaskLists_Lists));
    CU_ASSERT_PTR_NOT_NULL_FATAL(taskLists_Lists);
    int i;
    for (i = 0; i < 27; i++)
    {
        TaskListItem* item = malloc(sizeof (TaskListItem));
        item->id = (char *) malloc(2);
        item->id[0] = (char) i + 64;
        item->id[1] = '\0';
        CU_ASSERT_PTR_NOT_NULL_FATAL(item);

        addItemToTaskLists_Lists(taskLists_Lists, item);
        CU_ASSERT_EQUAL(taskLists_Lists->numberItems, i + 1);

        CU_ASSERT_PTR_NOT_NULL(&taskLists_Lists->items[i]);
        CU_ASSERT_STRING_EQUAL(taskLists_Lists->items[i].id, item->id);
        CU_ASSERT_PTR_EQUAL(taskLists_Lists->items[i].id, item->id);

    }
}

void testCreateNewTaskListItem()
{
    char *jsonFullPath = getFullFileName("taskListItem_valid.json");

    int errorCode = 0;
    char *fileContent = getFileContent(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    
    
    TaskListItem *result = createNewTaskListItem(value);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->etag);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->id);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->kind);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->selfLink);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->title);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->updated);
    CU_ASSERT_STRING_EQUAL(result->etag, "etag_string");
    CU_ASSERT_STRING_EQUAL(result->id, "id_string");
    CU_ASSERT_STRING_EQUAL(result->kind, "tasks#taskList");
    CU_ASSERT_STRING_EQUAL(result->selfLink, "selfLink_string");
    CU_ASSERT_STRING_EQUAL(result->updated, "datetime");
    

    free(result);
    json_value_free(value);

    char *jsonFullPath2 = getFullFileName("taskListItem_NOT_valid.json");
    char *fileContent2 = getFileContent(jsonFullPath2, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_value *value2 = json_parse_ex(&settings, fileContent2, error);
    TaskListItem *result2 = createNewTaskListItem(value2);


    CU_ASSERT_EQUAL(sizeof (result2->id), sizeof (char *));
    CU_ASSERT_EQUAL(sizeof (result2->kind), sizeof (char *));
    CU_ASSERT_EQUAL(sizeof (result2->etag), sizeof (char *));
    CU_ASSERT_EQUAL(sizeof (result2->selfLink), sizeof (char *));
    CU_ASSERT_EQUAL(sizeof (result2->title), sizeof (char *));
    CU_ASSERT_EQUAL(sizeof (result2->updated), sizeof (char *));
    
    free(result2);
    json_value_free(value2);
}

void testCreateNewTaskLists_ListsFromJson()
{
    char *jsonFullPath = getFullFileName("taskListLists_valid.json");

    int errorCode = 0;
    char *fileContent = getFileContent(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);
    
    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    
    
    TaskLists_Lists* result = createNewTaskLists_ListsFromJson(value);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->etag);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->kind);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->nextPageToken);
    CU_ASSERT_EQUAL(result->numberItems, 1);
    CU_ASSERT_STRING_EQUAL(result->etag, "etag_string");
    CU_ASSERT_STRING_EQUAL(result->kind, "tasks#taskLists");
    CU_ASSERT_STRING_EQUAL(result->nextPageToken, "nextPageToken_string");
    
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0]);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].etag);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].id);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].kind);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].selfLink);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].title);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result->items[0].updated);
    CU_ASSERT_STRING_EQUAL(result->items[0].etag, "etag_string");
    CU_ASSERT_STRING_EQUAL(result->items[0].id, "id_string");
    CU_ASSERT_STRING_EQUAL(result->items[0].kind, "tasks#taskList");
    CU_ASSERT_STRING_EQUAL(result->items[0].selfLink, "selfLink_string");
    CU_ASSERT_STRING_EQUAL(result->items[0].updated, "datetime");
    
    
}

void testDeleteItemFromTaskLists_list()
{
    TaskLists_Lists* taskLists_Lists;
    char* item;
    deleteItemFromTaskLists_list(taskLists_Lists, item);
    if (1 /*check result*/)
    {
        CU_ASSERT(1);
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
