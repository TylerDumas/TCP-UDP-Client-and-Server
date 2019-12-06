/*
 * CS 3873-001 TCP Client
 * author: Jackson Dumas
 *
 * main.c
 *
 * Purpose:
 * The Client portion of the Client/Server TCP connection.
 * Implements socket programming to establish a TCP connection to a server and
 * send/receive messages to/from it
 *
 * Notes:
 *  Most functionality is written in client.c,
 *  this is the driver program
*/

#include "./client.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_DATA_SIZE 99

/* Function Declarations */
void print_prompt();

/*
 * Function: main
 * The main/driver function for the server program.
 * Calls all necessary functions to execute the program.
 *
 * Param: argc  |   integer number of command line arguments passed
 * Param: argv  |   char** holding all string command line arguments passed
 *
 * returns:
 *      0   |   exited successfully
 *     !0   |   exited unsuccessfully
 */
int main() {
    /* Print the usage instructions/initial prompt */
    print_prompt();

    /* Execute the Client and handle non-zero exit status */
    if( execute_client( SERVER_IP, SERVER_PORT, MAX_DATA_SIZE ) != 0 ){
        return 1;
    }
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
 * Returns:
 *  None
 */
void print_prompt(){
    printf( "\nCS 3873-001 Project 3\n" );
    printf( "------------------------------------\n" );
    printf( "Author: Jackson Dumas(llt190)\n\n" );
    printf( "This is the TCP client program\n" );
    printf( "Usage:\tUpon being prompted, please enter your message to send to the server.\n" );
    printf( "\tYou can also enter one of the following commands (case sensitive)\n" );
    printf( "Commands:\n" );
    printf( "\t'.exit':\texits the program\n" );
    printf( "\t'.print':\tprint the current server information\n" );
    printf( "-----------------------------------------------------------------------\n\n" );
}