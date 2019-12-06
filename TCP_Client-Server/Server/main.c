/*
 * CS 3873-001 TCP Server
 * author: Jackson Dumas
 *
 * main.c
 *
 * Purpose:
 * The Server portion of the Client/Server TCP connection.
 * Implements socket programming to receive and respond to messages sent over a TCP connection
 *
 * Notes:
 *  Most functionality is written in server.c,
 *  this is the driver program
*/

#include "./server.h"

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

    /* Execute the Server and handle non-zero exit status */
    if( execute_server( SERVER_IP, SERVER_PORT, MAX_DATA_SIZE ) != 0 ){
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
 * Notes:
 *  This function is only called once, at program start
 *
 * Returns:
 *  None
 */
void print_prompt(){
    printf( "\nCS 3873-001 Project 4\n\n" );
    printf( "Author: Jackson Dumas(llt190)\n\n" );
    printf( "This is the TCP server program\n" );
    printf( "Usage:\tThis program requires no input.\n" );
    printf( "\tIf a client sends a message, the server will echo it automatically\n" );
    printf( "\tTo exit the program, use CTRL+C\n" );
    printf( "-------------------------------------------------------------------\n\n" );
}
