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
int appendString(char *destination, char *source);

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






#ifdef	__cplusplus
}
#endif

#endif	/* HELPERS_H */

