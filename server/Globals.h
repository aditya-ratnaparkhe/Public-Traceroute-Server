/*
 * Global header file used to define input default parameters
 * and other global variables.
 */


#include <stdio.h>

#ifndef traceroute_Globals_h
#define traceroute_Globals_h

#define PROMPT "\n>> "

#define ARG_PORT "--port"
#define ARG_STRICT_DESTINATION "--strict"
#define ARG_REQUEST_RATE  "--rate"
#define ARG_MAX_UESERS "--max_users"
#define ARG_REQUEST_RATE_TIME "--time"

#define TIMEOUT_INTERVAL 30
#define DEFAULT_TIME_UNIT 60
#define REQ_PER_SEC 4
#define PORT_NUMBER 1216
#define MAX_USERS 2
#define STRICT_DEST 0

#define SUCCESS 1
#define FAILURE 0


// "/Users/abhineet/Desktop/traceroute/traceroute/"
#define HELP_FILE "help.txt"
#define LOG_FILE "server_log.log"

#define SEPERATOR "\n-----------------------------------------------------------\n"
#define INVALID_COMMAND "\nInvalid Command\n"

typedef enum{
    TRCT_HOST_OR_IP,
    TRCT_ME,
    TRCT_FILE,
    HELP,
    QUIT,
    INVALID,
}CommandType;


#endif
