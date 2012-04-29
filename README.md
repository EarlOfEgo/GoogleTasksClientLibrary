#GoogleTasks Client library
A client library for get/update...
It uses the [json-parser](https://github.com/udp/json-parser) for parsing the json strings.
I will use this, when it is finished, to build an XFCE4 panel plugin.
##Status
At the moment it is possible to access google via Oauth2, request an access token and refresh it.

To execute the tests type:
    $make test
At the moment there are two dummy files: "client.id.for.git" and "client.secret.for.git".
They being used for testing the google oauth2 methods(with Cunit)
##Oauth2
`int initClientInformation(char *clientIdFile, char *clientSecretFile)` must be called first, with the name of the file which includes the client id and a file with the client secret.

`buildAccessTokenRequestAsHtmlRequest()` returns a string which needs to be copied in the browser. After this the user have to confirm the access.

`buildPostFieldsForRequestingAnAccessToken(char *accessTokenCode)` returns the postfilds, this can be used when making a https request.(accessTokenCode is the code that needs to be copied from the browser).

`buildPostFieldsForRefreshingTheAccessToken(char *refreshToken)` if the 
token was expired. Here the refresh token is needed, not the access token!.


###Requirements
Until now, just libcurl and cunit for the unit tests

