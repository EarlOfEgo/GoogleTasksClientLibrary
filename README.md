#GoogleTasks Client library
A client library for get/update...
It uses the [json-parser](https://github.com/udp/json-parser) for parsing the json strings.
I will use this, when it is finished, to build an XFCE4 panel plugin.
##Status
At the moment it is possible to access google via Oauth2, request an access token and refresh it.

To execute the tests type:
 ```~$make test
```
At the moment there are two dummy files: "client.id.for.git" and "client.secret.for.git".
They being used for testing the google oauth2 methods(with Cunit), for testing with real client id/secret write a small main:
```c
#include <stdio.h>
#include <stdlib.h>
#include "googleOauth2Access.h"

int main(int argc, char** argv) {

    initClientInformation("client_file_name, "client_secret_name");
    printf("Insert this in your browser:\n%s\n\nCopy the id and paste it:\n", buildAccessTokenRequestAsHtmlRequest());

    char str[255] = {'\0'};
    gets(str);
    
    printf("Google response:\n%s\n", makeHttpsRequestWithResponse(buildPostFieldsForRequestingAnAccessToken(&str), TOKEN_SERVER));
    
    return (EXIT_SUCCESS);
}
```
And run: 
```~$make
```
###Requirements
Until now, just libcurl and cunit for the unit tests
