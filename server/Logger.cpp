/*
 * Logger source file containing logging methods.
 */

#include "Logger.h"
#include "Globals.h"
#include <stdlib.h>
#include <cstring>
using namespace std;
FILE *log;

/*
 * returns the current timestamp.
 */
char* getTimeStamp()
{

    time_t currTime = time(NULL);
    struct tm *now = localtime(&currTime);
    char *timeString = new char[80]();
    strftime(timeString, 80, "%m/%d/%y %H:%M:%S", now);
    return timeString;
}

/*
 * Initialise by reading log file in append mode
 */
int initLogger()
{
    log = NULL;
    log = fopen(LOG_FILE, "a");
    return (log==NULL)?FAILURE:SUCCESS;
    

}

/*
 * Logs initialisation of server process
 */
void serverStartedLog()
{
    if(initLogger())
    {
        char *logMessage = new char[256]();
        strcat(logMessage, SEPERATOR);
        char *timestamp = getTimeStamp();
        strcat(logMessage,timestamp);
        free(timestamp);
        strcat(logMessage, " : ");
        strcat(logMessage, "Server started");
        if((fprintf(log, "\n%s",logMessage)<0))
            cout<<"Error logging";
        free(logMessage);
        fclose(log);
    }
}

/*
 * Logs client connection
 */
void clientConnectedLog(char *ipaddress,int port_no)
{
    if(initLogger())
    {
        char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Client Connected | IP: %s | Port: %d ",timestamp,ipaddress,port_no)<0))
            cout<<"Error logging";
                free(timestamp);
        fclose(log);
    }
}

/*
 * Logs execution of traceroute command.
 */
void simpleTrtLog(char *ipaddress,char* ipOrhostname, int port_no)
{
    if(initLogger())
    {
        char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Traceroute %s | from IP: %s PORT: %d ",timestamp,ipOrhostname,ipaddress,port_no)<0))
            cout<<"Error logging";
        free(timestamp);
        fclose(log);
    }

}

/*
 * Logs disconnection of client
 */

void clientDisconnetedLog(char *ipaddress, int port_no)
{
    if(initLogger())
    {
        char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Client Disconnected | from IP: %s PORT: %d ",timestamp,ipaddress,port_no)<0))
            cout<<"Error logging";
        free(timestamp);
        fclose(log);
    }
    

}
void clinetForceDisconnectLog(char *ipaddress, int port_no)
{
    
}

/*
 * Logs max connections error.
 */
void simultaneousConnectionLimitExccededLog(char *ipaddress,int port_no)
{
    if(initLogger())
    {
        char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Maximum connections excceded  | Disconnecting | Client IP: %s PORT: %d ",timestamp,ipaddress,port_no)<0))
            cout<<"Error logging";
        free(timestamp);
        fclose(log);
    }

    
}

/*
 * Logs voilation of strict = 1 condition
 */
void strictviolatedLog(char *ipaddress, int port_no, char *command)
{
    if(initLogger())
    {
           char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Strict violated  | Client IP: %s PORT: %d COMMAND: %s",timestamp,ipaddress,port_no,command)<0))
            cout<<"Error logging";
        free(timestamp);

        fclose(log);
    }

    
}

/*
 * Logs auto timeout of client
 */
void automaticTimeOutLog(char *ipaddress, int port_no)
{
    if(initLogger())
    {
           char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Connection Timeout  | Client IP: %s PORT: %d",timestamp,ipaddress,port_no)<0))
            cout<<"Error logging";
        free(timestamp);

        fclose(log);
    }
    
    
}

/*
 * Logs rate limit exceeded event
 */
void rateLimitExceededLog(char *ipaddress, int port_no, char *command)
{
    if(initLogger())
    {
           char *timestamp = getTimeStamp();
        if((fprintf(log, "\n%s : Rate Limit Exceeded  | Client IP: %s PORT: %d COMMAND: %s",timestamp,ipaddress,port_no,command)<0))
            cout<<"Error logging";
        free(timestamp);

        fclose(log);
    }

}
