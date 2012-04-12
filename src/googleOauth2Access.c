/* 
 * File:   googleOauth2Access.h
 * Author: stephan
 *
 * Created on April 12, 2012, 3:53 PM
 */

#include <string.h>
#include <stdlib.h>

#include "googleOauth2Access.h"

char *buildAccessTokenRequest()
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

char *buildPostFields(char *accessTokenCode)
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

char *validateAccessToken(char *postfields)
{
    CURL *curl;
    curl = curl_easy_init();

    if (!curl)
    {
        printf("ERROR");
        return NULL;
    }
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, TOKEN_SERVER);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(postfields));
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30000 / 1000);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, validateAccessTokenCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);


    return response;
}

size_t static validateAccessTokenCallback(void *ptr, size_t size, size_t nmemb, void *data)
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
    char *ret_val = malloc(strlen(str) * sizeof(char));
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
    char *ret_val = malloc(strlen(str) * sizeof(char));
    strcpy(ret_val, str);
    
    return ret_val;
}