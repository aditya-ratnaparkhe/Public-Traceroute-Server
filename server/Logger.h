/*
 * Header file for logger
 */

#ifndef __traceroute__Logger__
#define __traceroute__Logger__

#include <iostream>
int initLogger();
void serverStartedLog();
void clientConnectedLog(char *ipaddress, int portno);
void simpleTrtLog(char *ipaddress,char* ipOrhostname, int port_no);
void clientDisconnetedLog(char *ipaddress, int port_no);
void clinetForceDisconnectLog(char *ipaddress,int port_no);
void simultaneousConnectionLimitExccededLog(char *ipaddress,int port_no);
void strictviolatedLog(char *ipaddress, int port_no, char *command);
void automaticTimeOutLog(char *ipaddress, int port_no);
void rateLimitExceededLog(char *ipaddress, int port_no, char *command);

#endif /* defined(__traceroute__Logger__) */
