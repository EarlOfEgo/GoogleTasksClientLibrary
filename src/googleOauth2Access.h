/* 
 * File:   googleOauth2Access.h
 * Author: stephan
 *
 * Created on April 12, 2012, 3:53 PM
 */

#ifndef GOOGLEOAUTH2ACCESS_H
#define	GOOGLEOAUTH2ACCESS_H

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

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

    
char *buildAccessTokenRequest();
char *buildPostFields(char *accessTokenCode);

char *validateAccessToken(char *postfields);

size_t static validateAccessTokenCallback(void *ptr, size_t size, size_t nmemb, void *data);

char *readClientId();
char *readClientSecret();

typedef struct
{
    char *access_token;
    char *token_type;
    char *expires_in;
    char *refresh_token;
}TokenResponse;

void processIncommingTokenResponse(char *response);

FILE *fd;



#ifdef	__cplusplus
}
#endif

#endif	/* GOOGLEOAUTH2ACCESS_H */

