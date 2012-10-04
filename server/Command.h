/*
 * Header file for commands
 */

#ifndef __traceroute__Command__
#define __traceroute__Command__


#include <iostream>
#include <string.h>
#include "Globals.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <new>
using namespace std;

class Command {
 
 public:
    char    *orignal_command;
    char    *command;
    char    *args[10];
    int     total_args;
    CommandType cmdType;
     
    
/*
 * constructor for command entered by user
 */
    Command(char *userInput)
    {
        
         //Make copy of orignal command
        orignal_command = new char[1024]();
         command=new char[1024]();
        total_args=0;
        for (int i=0,j=0; i<strlen(userInput); i++)
        {
            if(!(iscntrl(userInput[i])))
                orignal_command[j++]=userInput[i];
                
        }
             
         const char *seperator = " ";
         char *token = strtok(orignal_command, seperator);
         if(token!=NULL)
         {
             strcpy(command, token);
             total_args = 0;
             while( (token =  strtok(NULL,seperator))!=NULL)
             {
                 args[total_args] = new char[1024]();
                 args[total_args] = token;
                 total_args++;
                 
             }

             
         }
    }
};

#endif /* defined(__traceroute__Command__) */
