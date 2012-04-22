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


#include "helpers.h"


int addQuotes(char *string)
{
    int length = strlen(string) + strlen("\"") +1;
    string = realloc(string, length);
    strcat(string, "\"");
    return length;
}

int addColon(char *string)
{
    int length = strlen(string) + strlen(":")+1;
    string = realloc(string, length);
    strcat(string, ":");
    return length;
}

int addComma(char *string)
{
    int length = strlen(string) + strlen(",") +1;
    string = realloc(string, length);
    strcat(string, ",");
    return length;
}


int appendString(char *destination, char *source)
{
    
    int length = strlen(destination) + strlen(source) + 1;
    
    destination = realloc(destination, length);
    strcat(destination, source);
    return length;
}


/**
 * If server sends a response.
 * @param ptr
 * @param size
 * @param nmemb
 * @param data
 * @return 
 */
size_t httpsCallback(void *ptr, size_t size, size_t nmemb, void *data)
{

    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) data;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        exit(EXIT_FAILURE);
    }

    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}




size_t readCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct WriteThis *writeThis = (struct WriteThis *) userp;

    if (size * nmemb < 1)
        return 0;

    if (writeThis->sizeleft)
    {
        *(char *) ptr = writeThis->readptr[0];
        writeThis->readptr++;
        writeThis->sizeleft--;
        return 1;
    }

    return 0;
}