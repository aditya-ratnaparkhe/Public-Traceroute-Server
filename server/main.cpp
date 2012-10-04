/*
 * Main file containing main()
 */

#include <iostream>
#include <unistd.h>
#include "ServerSoc.h"
#include "Globals.h"




int main(int argc, const char * argv[])
{
    
    Socket *server = Socket::shared();

     if((server->createSocket())>0)
        cout<<"\nError Creating Socket";
    else
        cout<<"\nSocket created";
 
    
    const char *seperator = "=";
    for(int i=1;i<argc;i++)
        //0 is command
    {
        const char *arg = argv[i];
        char *param = strtok((char *)arg, seperator);
        char *val = NULL;
        while ((val = strtok(NULL, seperator))!=NULL) {
         
            if(strcmp(param, ARG_PORT)==0)
                server->portNumber = atoi(val);
            else if((strcmp(param, ARG_STRICT_DESTINATION))==0)
                server->strictDestination = atoi(val);
            else if((strcmp(param, ARG_MAX_UESERS))==0)
                server->maximum_users = atoi(val);
            else if((strcmp(param, ARG_REQUEST_RATE))==0)
                server->reqPerMinPerUser = atoi(val);
            else if((strcmp(param, ARG_REQUEST_RATE_TIME))==0)
                server->timeUnit = atoi(val);

        }
    }

    

    server->startServerProcess();
    

    
    return 0;
}



