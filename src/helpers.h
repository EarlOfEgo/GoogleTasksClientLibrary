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

#ifndef HELPERS_H
#define	HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif

    
int addComma(char *string);
int addColon(char *string);
int addQuotes(char *string);
char* appendString(char *destination, const char *source);

struct MemoryStruct 
{
    char *memory;
    size_t size;
};

struct WriteThis 
{
    const char *readptr;
    long sizeleft;
};


size_t httpsCallback(void *ptr, size_t size, size_t nmemb, void *data);
size_t readCallback(void *ptr, size_t size, size_t nmemb, void *userp);


/***
 CONSTANTS
 */

static const char* TYPE_STRING = "type";
static const char* DESCRIPTION_STRING = "description";
static const char* LINK_STRING = "link";
static const char* PARENT_STRING = "parent";
static const char* POSITION_STRING = "position";
static const char* NOTES_STRING = "notes";
static const char* STATUS_STRING = "status";
static const char* DUE_STRING = "due";
static const char* COMPLETED_STRING = "completed";
static const char* DELETED_STRING = "deleted";
static const char* HIDDEN_STRING = "hidden";
    
static const char* TASKLISTS_STRING = "tasks#taskLists";
static const char* KIND_STRING = "kind";
static const char* ETAG_STRING = "etag";
static const char* NEXTPAGETOKEN_STRING = "nextPageToken";
static const char* TASKLISTITEM_STRING = "tasks#taskList";
static const char* ID_STRING = "id";
static const char* TITLE_STRING = "title";
static const char* UPDATED_STRING = "updated";
static const char* SELFLINK_STRING = "selfLink";
static const char* REDIRECT_URI =  "urn:ietf:wg:oauth:2.0:oob";
static const char* AUTH_SERVER =  "https://accounts.google.com/o/oauth2/auth";
static const char* SCOPE = "https://www.googleapis.com/auth/tasks";
static const char* TOKEN_SERVER = "https://accounts.google.com/o/oauth2/token";
static const char* QUESTIONMARK = "?";

static const char *AND = "&";
static const char* CLIENT_ID_STRING = "client_id=";
static const char* CLIENT_SECRET_STRING = "client_secret=";
static const char* REDIRECT_URI_STRING = "redirect_uri=";
static const char* SCOPE_STRING = "scope=";
static const char* RESPONSE_TYPE_STRING = "response_type=";
static const char* CODE = "code";
static const char* CODE_STRING = "code=";
static const char* ACCESS_TYPE_STRING = "access_type=";
static const char* ACCESS_TYPE_OFFLINE = "offline";
static const char* GRANT_TYPE_STRING = "grant_type=";
static const char* AUTHORIZATION_CODE = "authorization_code";

static const char* ACCESS_TOKEN = "access_token";
static const char* EXPIRES_IN = "expires_in";
static const char* TOKEN_TYPE = "token_type";
static const char* REFRESH_TOKEN = "refresh_token";

static const char* REFRESH_TOKEN_STRING = "refresh_token=";
static const char* ACCESS_TOKEN_STRING = "access_token=";

static const char* NO_ERROR = "NO_ERROR";
static const char* ERROR = "error";
static const char* INVALID_GRAND_STRING = "invalid_grant";

static const char* TASKS_HTTP_REQUEST = "https://www.googleapis.com/tasks/v1/lists";
static const char* HEADER_AUTHORIZATION = "Authorization:  Bearer ";

static const char* MAX_RESULTS_STRING = "maxResults=";
static const char* PAGE_TOKEN_STRING = "pageToken=";
static const char* FIELDS_STRING = "fields=";

#ifdef	__cplusplus
}
#endif

#endif	/* HELPERS_H */

