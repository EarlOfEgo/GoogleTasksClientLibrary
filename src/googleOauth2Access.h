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

#ifndef GOOGLEOAUTH2ACCESS_H
#define	GOOGLEOAUTH2ACCESS_H

#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "json.h"

#ifdef	__cplusplus
extern "C" {
#endif
  
#define REDIRECT_URI "urn:ietf:wg:oauth:2.0:oob"
#define AUTH_SERVER "https://accounts.google.com/o/oauth2/auth"
#define SCOPE "https://www.googleapis.com/auth/tasks"
#define TOKEN_SERVER "https://accounts.google.com/o/oauth2/token"
#define QUESTIONMARK "?"
#define AND "&"

#define CLIENT_ID_STRING "client_id="
#define CLIENT_SECRET_STRING "client_secret="
#define REDIRECT_URI_STRING "redirect_uri="
#define SCOPE_STRING "scope="
#define RESPONSE_TYPE_STRING "response_type="
#define CODE "code"
#define CODE_STRING "code="
#define ACCESS_TYPE_STRING "access_type="
#define ACCESS_TYPE_OFFLINE "offline"
#define GRANT_TYPE_STRING "grant_type="
#define AUTHORIZATION_CODE "authorization_code"
    
#define ACCESS_TOKEN "access_token"
#define EXPIRES_IN "expires_in"
#define TOKEN_TYPE "token_type"
#define REFRESH_TOKEN "refresh_token"

#define REFRESH_TOKEN_STRING "refresh_token="
#define ACCESS_TOKEN_STRING "access_token="
    
#define NO_ERROR "NO_ERROR"
#define ERROR "error"
#define INVALID_GRAND_STRING "invalid_grant"
    
/* GOOGLE RESPONSE ERROR CODES */
#define INVALID_GRAND 20
   
    
char *buildAccessTokenRequestAsHtmlRequest();
char *buildPostFieldsForRequestingAnAccessToken(char *accessTokenCode);
char *buildPostFieldsForRefreshingTheAccessToken(char *refreshToken);

char *makeHttpsRequestWithResponse(char *postfields, char *https_server);
size_t static httpsCallbackOauth(void *ptr, size_t size, size_t nmemb, void *data);


char *getFileContent(char *path, int *errorCode);
char *getFullFileName(char *fileName);


typedef struct
{
    char *access_token;
    char *token_type;
    int expires_in;
    char *refresh_token;
    char *error_code;
}TokenResponse;

typedef struct
{
    char *client_secret;
    char *client_id;
}ClientInformation;

ClientInformation *clientInformation ;

/* HAVE TO BE CALLED FIRST */
int initClientInformation(char *clientIdFile, char *clientSecretFile);

TokenResponse *processIncomingAccessTokenResponse(json_value *value);
TokenResponse *processIncomingRefreshTokenResponse(json_value *value, char *refreshToken);


int checkIfErrorOccured(json_value *value);


#ifdef	__cplusplus
}
#endif

#endif	/* GOOGLEOAUTH2ACCESS_H */

