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

#include <string.h>
#include <stdlib.h>

#include "googleOauth2Access.h"

/**
 * Builds the access token request, the user has to copy this address into his browser and allow the application to access his account.
 * @return the url as a string.
 */
char *buildAccessTokenRequestAsHtmlRequest() //TODO: REFACTOR AFTER ALL TESTS SUCCEED.... //TODO: WRITE TESTS!!
{

    int str_lenght = strlen(AUTH_SERVER) + 1;
    char *ret_value =  malloc(str_lenght * sizeof (char));
    strcpy(ret_value, AUTH_SERVER);

    if (clientInformation->client_id == NULL || clientInformation->client_secret == NULL)
    {
        printf("ERROR");
        return NULL;
    }

	ret_value = appendString(ret_value, QUESTIONMARK);
    	ret_value = appendString(ret_value, CLIENT_ID_STRING);
    char *client_id = clientInformation->client_id;
  	ret_value = appendString(ret_value, client_id);
	ret_value = appendString(ret_value, AND);
	ret_value = appendString(ret_value, REDIRECT_URI_STRING);
	ret_value = appendString(ret_value, REDIRECT_URI);
	ret_value = appendString(ret_value, AND);
	ret_value = appendString(ret_value, SCOPE_STRING);
	ret_value = appendString(ret_value, SCOPE);
	ret_value = appendString(ret_value, AND);
	ret_value = appendString(ret_value, RESPONSE_TYPE_STRING);
	ret_value = appendString(ret_value, CODE);
	ret_value = appendString(ret_value, AND);
	ret_value = appendString(ret_value, ACCESS_TYPE_STRING);
	ret_value = appendString(ret_value, ACCESS_TYPE_OFFLINE);

    return ret_value;
}

/**
 * Build the post fields for the access token request, separated by '&'.
 * @param accessTokenCode
 * @return the post fields as a string
 */
char *buildPostFieldsForRequestingAnAccessToken(const char *accessTokenCode)//TODO: REFACTOR AFTER ALL TESTS SUCCEED.... //TODO: WRITE TESTS!!
{

    int str_lenght = strlen(CODE_STRING) + 1;
    char *ret_value = malloc(str_lenght * sizeof (char));
    strcpy(ret_value, CODE_STRING);

    str_lenght += strlen(accessTokenCode);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, accessTokenCode);
	
    ret_value = appendString(ret_value, AND);
    
        str_lenght += strlen(CLIENT_ID_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_ID_STRING);

    char *client_id = clientInformation->client_id;
    str_lenght += strlen(client_id);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_id);

    ret_value = appendString(ret_value, AND);

    str_lenght += strlen(CLIENT_SECRET_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_SECRET_STRING);

    char *client_secret = clientInformation->client_secret;
    str_lenght += strlen(client_secret);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_secret);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(REDIRECT_URI_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, REDIRECT_URI_STRING);

    str_lenght += strlen(REDIRECT_URI);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, REDIRECT_URI);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(GRANT_TYPE_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, GRANT_TYPE_STRING);

    str_lenght += strlen(AUTHORIZATION_CODE);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AUTHORIZATION_CODE);

    return ret_value;
}

/**
 * Builds the post fields for the refresh access token request, separated with '&'
 * @param refreshToken
 * @return 
 */
char *buildPostFieldsForRefreshingTheAccessToken(char *refreshToken)//TODO: REFACTOR AFTER ALL TESTS SUCCEED.... //TODO: WRITE TESTS!!
{
    int str_lenght = strlen(REFRESH_TOKEN_STRING) + 1;
    char *ret_value = malloc(str_lenght * sizeof (char));
    strcpy(ret_value, REFRESH_TOKEN_STRING);

    str_lenght += strlen(refreshToken);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, refreshToken);

    ret_value = appendString(ret_value, AND);

    str_lenght += strlen(CLIENT_ID_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_ID_STRING);

    char *client_id = clientInformation->client_id;
    str_lenght += strlen(client_id);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_id);

    ret_value = appendString(ret_value, AND);

    str_lenght += strlen(CLIENT_SECRET_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_SECRET_STRING);

    char *client_secret = clientInformation->client_secret;
    str_lenght += strlen(client_secret);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_secret);

    ret_value = appendString(ret_value, AND);

    str_lenght += strlen(GRANT_TYPE_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, GRANT_TYPE_STRING);

    str_lenght += strlen(REFRESH_TOKEN);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, REFRESH_TOKEN);

    return ret_value;
}

/**
 * Makes an Https request to the given server.
 * @param postfields
 * @return the resonse
 */
char *makeHttpsRequestWithResponse(char *postfields, char *https_server)
{
    CURL *curl;
    curl = curl_easy_init();

    if (!curl)
    {
        printf("ERROR");
        return NULL;
    }
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, https_server);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(postfields));
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30000 / 1000);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallbackOauth);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);


    return response;
}

/**
 * If server sends a response.
 * @param ptr
 * @param size
 * @param nmemb
 * @param data
 * @return 
 */
size_t static httpsCallbackOauth(void *ptr, size_t size, size_t nmemb, void *data)
{

    char **res_ptr = (char**) data;
    *res_ptr = strndup(ptr, (size_t) (size * nmemb));
}

/**
 * Processes the incoming response from the request of an access token
 * @param response
 * @return TokenResponse struct
 */
TokenResponse *processIncomingAccessTokenResponse(json_value *value)
{
    TokenResponse *tokenResponse = malloc(sizeof (TokenResponse));
    tokenResponse->error_code = malloc(strlen(NO_ERROR) + 1);
    strcpy(tokenResponse->error_code, NO_ERROR);
    if (value != NULL)
    {
        if (value->u.object.length == 1 && strcmp(value->u.object.values[0].name, "error") == 0)
        {
            tokenResponse->error_code = realloc(tokenResponse->error_code, value->u.object.values[0].value->u.string.length + 1);
            strcpy(tokenResponse->error_code, value->u.object.values[0].value->u.string.ptr);
            printf("%s\n", value->u.object.values[0].value->u.string.ptr);
            json_value_free(value);
            return tokenResponse;
        }

        int i;
        for (i = 0; i < value->u.object.length; i++)
        {
            if (value->u.object.values[i].value->type != json_array)
            {
                if (strcmp(value->u.object.values[i].name, ACCESS_TOKEN) == 0)
                {
                    tokenResponse->access_token = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(tokenResponse->access_token, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, EXPIRES_IN) == 0)
                {
                    tokenResponse->expires_in = value->u.object.values[i].value->u.integer;
                } else if (strcmp(value->u.object.values[i].name, TOKEN_TYPE) == 0)
                {
                    tokenResponse->token_type = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(tokenResponse->token_type, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, REFRESH_TOKEN) == 0)
                {
                    tokenResponse->refresh_token = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(tokenResponse->refresh_token, value->u.object.values[i].value->u.string.ptr);
                }
            }

        }
    }
    return tokenResponse;
}

/**
 * Processes the incoming response from the request of the refresh of an access token
 * @param response
 * @param refreshToken
 * @return TokenResponse struct
 */
TokenResponse *processIncomingRefreshTokenResponse(json_value *value, char *refreshToken)
{
    TokenResponse *tokenResponse = malloc(sizeof (TokenResponse));

    tokenResponse->refresh_token = malloc(strlen(refreshToken) + 1);
    strcpy(tokenResponse->refresh_token, refreshToken);

    tokenResponse->error_code = malloc(strlen(NO_ERROR) + 1);
    strcpy(tokenResponse->error_code, NO_ERROR);

    if (value != NULL)
    {
        if (value->u.object.length == 1 && strcmp(value->u.object.values[0].name, "error") == 0)
        {
            tokenResponse->error_code = malloc(value->u.object.values[0].value->u.string.length + 1);
            strcpy(tokenResponse->error_code, value->u.object.values[0].value->u.string.ptr);
            printf("%s\n", value->u.object.values[0].value->u.string.ptr);
            json_value_free(value);
            return tokenResponse;
        }

        int i;
        for (i = 0; i < value->u.object.length; i++)
        {
            if (value->u.object.values[i].value->type != json_array)
            {
                if (strcmp(value->u.object.values[i].name, ACCESS_TOKEN) == 0)
                {
                    tokenResponse->access_token = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(tokenResponse->access_token, value->u.object.values[i].value->u.string.ptr);
                } else if (strcmp(value->u.object.values[i].name, EXPIRES_IN) == 0)
                {
                    tokenResponse->expires_in = value->u.object.values[i].value->u.integer;
                } else if (strcmp(value->u.object.values[i].name, TOKEN_TYPE) == 0)
                {
                    tokenResponse->token_type = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(tokenResponse->token_type, value->u.object.values[i].value->u.string.ptr);
                }
            }

        }
    }
    return tokenResponse;
}

char *getFullFileName(char *fileName)
{
    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof (cCurrentPath) / sizeof (char)))
    {
        return NULL;
    }
    strcat(cCurrentPath, "/");
    char *fullFileName = malloc(strlen(&cCurrentPath) + strlen(fileName) + 1);
    strcpy(fullFileName, &cCurrentPath);
    strcat(fullFileName, fileName);
    return fullFileName;
}

char *getFileContent(char *path, int *errorCode)
{
    size_t length;
    size_t bytesToRead;
    char* content;
    FILE* f;

    f = fopen(path, "rb");
    if (f == NULL)
    {
        *errorCode = 1;
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    rewind(f);


    content = malloc(sizeof (char) * length +1);
    if (content == NULL)
    {
        *errorCode = 2;
        return NULL;
    }
 
    memset(content, '\0', length+1);
    bytesToRead = fread(content, sizeof (char), length, f);

    fclose(f);

    if (content[length - 1] == '\n')
    {
        content[length - 1] = '\0';
    }
    return content;
}

int initClientInformation(char *clientIdFile, char *clientSecretFile)
{
    int errorCode = 0;
    clientInformation = malloc(sizeof (ClientInformation));
    const char* client_id = getFileContent(getFullFileName(clientIdFile), &errorCode);
    if (errorCode != 0)
        return errorCode;
    const char* client_secret = getFileContent(getFullFileName(clientSecretFile), &errorCode);
    if (errorCode != 0)
        return errorCode;
    clientInformation->client_id = malloc(strlen(client_id) + 1);
    strcpy(clientInformation->client_id, client_id);

    clientInformation->client_secret = malloc(strlen(client_secret) + 1);
    strcpy(clientInformation->client_secret, client_secret);

    return errorCode;
}

/**
 * Checks if google sends an error and returns an integer with the responding error code.
 * @param value
 * @return the error code as an integer
 */
int checkIfErrorOccured(json_value *value)
{
    int returnValue = 0, i;
    if (value != NULL)
    {
        for (i = 0; i < value->u.object.length; i++)
        {
            if (strcmp(value->u.object.values[i].name, ERROR) == 0)
            {
                if (strcmp(value->u.object.values[i].value->u.string.ptr, INVALID_GRAND_STRING) == 0)
                {
                    returnValue = INVALID_GRAND;
                }
            }
        }
    }

    return returnValue;
}
