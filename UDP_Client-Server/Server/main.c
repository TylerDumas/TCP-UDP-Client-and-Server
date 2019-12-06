/*
 * CS 3873-001 UDP Server
 * author: Jackson Dumas
 *
 * main.c
 *
 * Purpose:
 *  The Server portion of the Client/Server UDP connection.
 *  Implements socket programming to receive messages from the client and send a response
 *
 * Notes:
 *  Most functionality is written in server.c,
 *  this is the driver program
*/

#include <stdio.h>
#include "./server.h"

/* Server Information */
#define SERVER_PORT 8080   //The port that the server is listening from
#define MAX_DATA_SIZE 99     //Maximum size of the string to send to the server

/* Function Declarations */
void print_prompt();

/*
 * Function: main
 *
 * Purpose:
 *  This is the driver program for the Server.
 *  Prints the initial program prompt and then executes the Server
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
    print_prompt();     //Print usage prompt
    execute_server( SERVER_PORT, MAX_DATA_SIZE );     //Execute server logic
    return 0;
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
 * Notes:
 *  This function is only called once, at program start
 *
 * Returns:
 *  None
 */
void print_prompt(){
    printf( "-----------------------------------------------------------------------------------------\n" );
    printf( "|\t\t\t\t\t\t\t\t\t\t\t|\n" );
    printf( "|\tCS 3873-001 Project 3\t\t\t\t\t\t\t\t|\n" );
    printf( "|\t------------------------------------\t\t\t\t\t\t|\n" );
    printf( "|\tAuthor: Jackson Dumas(llt190)\t\t\t\t\t\t\t|\n" );
    printf( "|\t\t\t\t\t\t\t\t\t\t\t|\n" );
    printf( "|\tThis is the UDP server program\t\t\t\t\t\t\t|\n" );
    printf( "|\tUsage:\tThis program requires no input.\t\t\t\t\t\t|\n" );
    printf( "|\t\tIf a client sends a message, the server will echo it automatically\t|\n" );
    printf( "|\t\tTo exit the program, use CTRL+C\t\t\t\t\t\t|\n" );
    printf( "|\t\t\t\t\t\t\t\t\t\t\t|\n" );
    printf( "-----------------------------------------------------------------------------------------\n\n" );
    printf( "\tListening for messages... standby\n\n\n" );
}
