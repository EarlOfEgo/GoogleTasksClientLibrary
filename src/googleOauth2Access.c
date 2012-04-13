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
char *buildAccessTokenRequestAsHtmlRequest()
{
    int str_lenght = strlen(AUTH_SERVER) + 1;
    char *ret_value = malloc(str_lenght * sizeof (char));
    strcpy(ret_value, AUTH_SERVER);

    str_lenght += strlen(QUESTIONMARK);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, QUESTIONMARK);

    str_lenght += strlen(CLIENT_ID_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_ID_STRING);

    char *client_id = readClientId();
    str_lenght += strlen(client_id);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_id);

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

    str_lenght += strlen(SCOPE_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, SCOPE_STRING);

    str_lenght += strlen(SCOPE);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, SCOPE);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(RESPONSE_TYPE_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, RESPONSE_TYPE_STRING);

    str_lenght += strlen(CODE);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CODE);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(ACCESS_TYPE_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, ACCESS_TYPE_STRING);

    str_lenght += strlen(ACCESS_TYPE_OFFLINE);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, ACCESS_TYPE_OFFLINE);

    return ret_value;
}

/**
 * Build the post fields for the access token request, separated by '&'.
 * @param accessTokenCode
 * @return the post fields as a string
 */
char *buildPostFieldsForRequestingAnAccessToken(char *accessTokenCode)
{
    int str_lenght = strlen(CODE_STRING) + 1;
    char *ret_value = malloc(str_lenght * sizeof (char));
    strcpy(ret_value, CODE_STRING);

    str_lenght += strlen(accessTokenCode);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, accessTokenCode);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(CLIENT_ID_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_ID_STRING);

    char *client_id = readClientId();
    str_lenght += strlen(client_id);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_id);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(CLIENT_SECRET_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_SECRET_STRING);

    char *client_secret = readClientSecret();
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
char *buildPostFieldsForRefreshingTheAccessToken(char *refreshToken)
{
    int str_lenght = strlen(REFRESH_TOKEN_STRING) + 1;
    char *ret_value = malloc(str_lenght * sizeof (char));
    strcpy(ret_value, REFRESH_TOKEN_STRING);

    str_lenght += strlen(refreshToken);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, refreshToken);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(CLIENT_ID_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_ID_STRING);

    char *client_id = readClientId();
    str_lenght += strlen(client_id);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_id);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(CLIENT_SECRET_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, CLIENT_SECRET_STRING);

    char *client_secret = readClientSecret();
    str_lenght += strlen(client_secret);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, client_secret);

    str_lenght += strlen(AND);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, AND);

    str_lenght += strlen(GRANT_TYPE_STRING);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, GRANT_TYPE_STRING);

    str_lenght += strlen(REFRESH_TOKEN);
    ret_value = realloc(ret_value, str_lenght);
    strcat(ret_value, REFRESH_TOKEN);
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpsCallback);
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
size_t static httpsCallback(void *ptr, size_t size, size_t nmemb, void *data)
{

    char **res_ptr = (char**) data;
    *res_ptr = strndup(ptr, (size_t) (size * nmemb));
}

char *readClientId()
{

    char str[200];

    fd = fopen("/home/stephan/Dropbox/Projects/client_id", "r");
    if (fd == NULL) return NULL;
    while (fgets(str, sizeof (str), fd) != NULL)
    {
        int len = strlen(str) - 1;
        if (str[len] == '\n')
            str[len] = 0;

    }
    fclose(fd);
    char *ret_val = malloc(strlen(str) * sizeof (char));
    strcpy(ret_val, str);

    return ret_val;
}

char *readClientSecret()
{
    char str[200];

    fd = fopen("/home/stephan/Dropbox/Projects/client_secret", "r");
    if (fd == NULL) return NULL;
    while (fgets(str, sizeof (str), fd) != NULL)
    {
        int len = strlen(str) - 1;
        if (str[len] == '\n')
            str[len] = 0;

    }
    fclose(fd);
    char *ret_val = malloc(strlen(str) * sizeof (char));
    strcpy(ret_val, str);

    return ret_val;
}

/**
 * Processes the incoming response from the request of an access token
 * @param response
 * @return TokenResponse struct
 */
TokenResponse *processIncomingAccessTokenResponse(char *response)
{
    json_value *value = json_parse(response);
    TokenResponse *tokenResponse = malloc(sizeof (TokenResponse));

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
                } else if (strcmp(value->u.object.values[i].name, REFRESH_TOKEN) == 0)
                {
                    tokenResponse->refresh_token = malloc(value->u.object.values[i].value->u.string.length + 1);
                    strcpy(tokenResponse->refresh_token, value->u.object.values[i].value->u.string.ptr);
                }
            }

        }
        json_value_free(value);
    }
    return tokenResponse;
}


/**
 * Processes the incoming response from the request of the refresh of an access token
 * @param response
 * @param refreshToken
 * @return TokenResponse struct
 */
TokenResponse *processIncomingTokenResponse(char *response, char *refreshToken)
{
    json_value *value = json_parse(response);
    TokenResponse *tokenResponse = malloc(sizeof (TokenResponse));
    tokenResponse->refresh_token = malloc(strlen(refreshToken) + 1);
    strcpy(tokenResponse->refresh_token, refreshToken);

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
        json_value_free(value);
    }
    return tokenResponse;
}