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
#include "src/googleOauth2Access.h"

/*
 * CUnit Test Suite
 */

int init_suite(void)
{
    initClientInformation("client.id.for.git", "client.secret.for.git");
    if(clientInformation == NULL)
        return CUEA_ABORT;
    return 0;
}

int clean_suite(void)
{
    return 0;
}

/* NOTE: IF YOU WANT TO TEST WITH OTHER CLIENT ID/SECRET, THE STING NEEDS TO BE EDITED 
 * DUMMY FILES WERE USED.
 */
void testBuildAccessTokenRequestAsHtmlRequest()
{
    char* result = buildAccessTokenRequestAsHtmlRequest();
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "https://accounts.google.com/o/oauth2/auth?client_id=CLIENT_ID_XYZ_123&redirect_uri=urn:ietf:wg:oauth:2.0:oob&scope=https://www.googleapis.com/auth/tasks&response_type=code&access_type=offline");
}

/* NOTE: IF YOU WANT TO TEST WITH OTHER CLIENT ID/SECRET, THE STING NEEDS TO BE EDITED 
 * DUMMY FILES WERE USED.
 */
void testBuildPostFieldsForRefreshingTheAccessToken()
{
    char* refreshToken = "REFRESH_TOKEN";
    char* result = buildPostFieldsForRefreshingTheAccessToken(refreshToken);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "refresh_token=REFRESH_TOKEN&client_id=CLIENT_ID_XYZ_123&client_secret=CLIENT_SECRET_FOR_GIT_XYZ_123&grant_type=refresh_token");


}

/* NOTE: IF YOU WANT TO TEST WITH OTHER CLIENT ID/SECRET, THE STING NEEDS TO BE EDITED 
 * DUMMY FILES WERE USED.
 */
void testBuildPostFieldsForRequestingAnAccessToken()
{
    char* accessTokenCode = "ACCESS_TOKEN";
    char* result = buildPostFieldsForRequestingAnAccessToken(accessTokenCode);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result, "code=ACCESS_TOKEN&client_id=CLIENT_ID_XYZ_123&client_secret=CLIENT_SECRET_FOR_GIT_XYZ_123&redirect_uri=urn:ietf:wg:oauth:2.0:oob&grant_type=authorization_code");


}

void testMakeHttpsRequestWithResponse()
{
    char* postfields;
    char* https_server;
    char* result = makeHttpsRequestWithResponse(postfields, https_server);
    CU_ASSERT_PTR_NULL(result);

}

void testProcessIncomingAccessTokenResponse()
{
    int errorCode = 0;
    char *jsonFullPath = getFullFileName("tests/jsons/googleOauth2AccessTokenResponse_valid.json");
    char *fileContent = getFileContent(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    TokenResponse* result = processIncomingAccessTokenResponse(value);
    
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result->access_token, "access_token_string");
    CU_ASSERT_STRING_EQUAL(result->error_code, NO_ERROR);
    CU_ASSERT_STRING_EQUAL(result->refresh_token, "refresh_token_string");
    CU_ASSERT_STRING_EQUAL(result->token_type, "Bearer");
    CU_ASSERT_EQUAL(result->expires_in, 3920);
    
    json_value_free(value);   

}

void testProcessIncomingRefreshTokenResponse()
{
    int errorCode = 0;
    char *jsonFullPath = getFullFileName("tests/jsons/googleOauth2RefreshTokenResponse_valid.json");
    char *fileContent = getFileContent(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];
    json_value *value = json_parse_ex(&settings, fileContent, error);
    char* refreshToken = "REFRESH_TOKEN";
    TokenResponse* result = processIncomingRefreshTokenResponse(value, refreshToken);
    CU_ASSERT_PTR_NOT_NULL_FATAL(result);
    CU_ASSERT_STRING_EQUAL(result->access_token, "refreshed_access_token");
    CU_ASSERT_STRING_EQUAL(result->error_code, NO_ERROR);
    CU_ASSERT_STRING_EQUAL(result->refresh_token, refreshToken);
    CU_ASSERT_STRING_EQUAL(result->token_type, "Bearer");
    CU_ASSERT_EQUAL(result->expires_in, 3920);
    
    json_value_free(value); 

}

void testcheckIfErrorOccured()
{

    int errorCode = 0;
    char *jsonFullPath = getFullFileName("tests/jsons/googleOauth2Access_invalidGrand.json");
    char *fileContent = getFileContent(jsonFullPath, &errorCode);
    CU_ASSERT_EQUAL_FATAL(errorCode, 0);
    CU_ASSERT_PTR_NOT_NULL_FATAL(fileContent);

    json_settings settings;
    memset(&settings, 0, sizeof (json_settings));
    char error[256];

    json_value *value = json_parse_ex(&settings, fileContent, error);
    CU_ASSERT_PTR_NOT_NULL_FATAL(value);
    
    int return_value = checkIfErrorOccured(value);
    CU_ASSERT_NOT_EQUAL(return_value, 0);
    CU_ASSERT_EQUAL(return_value, INVALID_GRAND);

    json_value_free(value); 
    
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("google_oauth2_access_test", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testBuildAccessTokenRequestAsHtmlRequest", testBuildAccessTokenRequestAsHtmlRequest)) ||
            (NULL == CU_add_test(pSuite, "testBuildPostFieldsForRefreshingTheAccessToken", testBuildPostFieldsForRefreshingTheAccessToken)) ||
            (NULL == CU_add_test(pSuite, "testBuildPostFieldsForRequestingAnAccessToken", testBuildPostFieldsForRequestingAnAccessToken)) ||
            (NULL == CU_add_test(pSuite, "testMakeHttpsRequestWithResponse", testMakeHttpsRequestWithResponse)) ||
            (NULL == CU_add_test(pSuite, "testProcessIncomingAccessTokenResponse", testProcessIncomingAccessTokenResponse)) ||
            (NULL == CU_add_test(pSuite, "testProcessIncomingRefreshTokenResponse", testProcessIncomingRefreshTokenResponse)) ||
            (NULL == CU_add_test(pSuite, "testcheckIfErrorOccured", testcheckIfErrorOccured)))
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
