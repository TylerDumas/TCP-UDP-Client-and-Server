/*
 * CS 3873-001 UDP Client
 * author: Jackson Dumas (ll190)
 *
 * main.c
 *
 * Purpose:
 *  The Client portion of the Client/Server UDP connection.
 *  Implements socket programming to send messages to the server and receive a response
 *
 * Notes:
 *  Most functionality is written in client.c,
 *  this is the driver program
*/

#include <stdio.h>
#include "./client.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_DATA_SIZE 99

/* Function Definitions */
void print_prompt( char *host_ip, int host_port );

/*
 * Function: main
 *
 * Purpose:
 *  This is the driver program for the client.
 *  Prints the initial program prompt and then executes the client
 *
 * Parameters:
 *  | argc      integer value of the number of command line arguments passed to this program
 *  | argv      character double pointer holding each command line argument
 *
 * Returns:
 *  | 0     exit status indicating success
 *  | !0    exit status indicating failure
*/
int main ( int argc, char **argv ){

    print_prompt( SERVER_IP, SERVER_PORT );     //Print usage prompt

    execute_client( SERVER_IP, SERVER_PORT, MAX_DATA_SIZE );     //Execute client logic

    return 0;   //Successfully exit
}

/*
 * Function: print_prompt
 *
 * Purpose:
 *  Simply prints the usage instructions and project information
 *
 * Parameters:
 *  None
 *
 * Returns:
 *  None
 */
void print_prompt( char *host_ip, int host_port ){
    printf( "-----------------------------------------------------------------------------------------\n" );
    printf( "|\t\t\t\t\t\t\t\t\t\t\t|\n" );
    printf( "|\tCS 3873-001 Project 3\t\t\t\t\t\t\t\t|\n" );
    printf( "|\t------------------------------------\t\t\t\t\t\t|\n" );
    printf( "|\tAuthor: Jackson Dumas(llt190)\t\t\t\t\t\t\t|\n" );
    printf( "|\t\t\t\t\t\t\t\t\t\t\t|\n" );
    printf( "|\tThis is the UDP client program\t\t\t\t\t\t\t|\n" );
    printf( "|\tUsage:\tUpon being prompted, please enter your message to send to the server.\t|\n" );
    printf( "|\t\tYou can also enter one of the following commands (case sensitive)\t|\n" );
    printf( "|\tCommands:\t\t\t\t\t\t\t\t\t|\n" );
    printf( "|\t\t'.exit':\texits the program\t\t\t\t\t|\n" );
    printf( "|\t\t'.print':\tprint the current server information\t\t\t|\n" );
    printf( "-----------------------------------------------------------------------------------------\n\n" );
}
