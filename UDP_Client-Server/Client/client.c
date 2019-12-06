/*
 * CS 3873-001 UDP Client
 * author: Jackson Dumas
 *
 * client.c
 *
 * Purpose:
 *  Contains implementation of Client functionality.
 *  Client functionality includes: connecting to server, sending UDP datagram,
 *  receiving server response, responding to server response
 *
 * Driver Program:
 *  main.c (Client)
 *
 * Notes:
 *  None
 */

#include "./client.h"

/******************************** Function Definitions ***************************************/

/*
 * Function: execute_client
 *
 * Purpose:
 * Calls helper functions to initialize all necessary server and client data,
 * also implements sending and receiving data to/from the server described in the parameters
 *
 * Parameters:
 *  | server_ip     string representation of the server's IPv4 address
 *  | port_num      int representation of the server's port number
 *  | data_size     the maximum size of the data(character array) to send to the server
 *
 * Notes:
 * This function holds the majority of the functionality of the client program
 * This includes the input loop.
 *
 * Returns:
 *  | None
 */
void execute_client( char *server_ip, int port_num, int data_size ){

    int socket_fd;  //Socket file descriptor
    int server_len;     //length of the server_addr struct

    char *buffer = malloc( data_size * sizeof( char ) );     //Initialize the message buffer(char array)
    char *response_buffer = malloc( data_size * sizeof( char ) );     //Initialize the server's response buffer

    /* Initialize Server information */
    struct sockaddr_in server_addr;
    initialize_server_address( server_ip, &server_addr, port_num );
    server_len = sizeof( server_addr );

    /* Create Client Socket */
    if ( (socket_fd = socket( AF_INET, SOCK_DGRAM ,IPPROTO_UDP ) ) < 0 ) {  //Check that socket was created successfully
        fprintf( stderr, "Failed to create the client socket\n" );  //Print error to stderr
        exit( EXIT_FAILURE );
    }

    /************* Client Input/Response loop **************/
    while ( 1 ) {

        /* Get Client message */
        if ( get_client_message(&buffer, data_size) != 0 || strlen(buffer) <= 1 ) {
            fprintf(stderr, "Failed to get a valid message, exiting\n");
            break;
        }
        
        /* check for commands */
        if ( strcmp( buffer, ".exit\n" ) == 0 ){        //exit the program
            printf( "Exiting the client\n" );
            break;
        }else if ( strcmp( buffer, ".print\n" ) == 0 ){     //print the server info
            printf( "\n-----------------------------------------------------------------------------\n" );
            printf( "|\t\t\t\t\t\t\t\t\t    |\n" ); 
            printf( "|\tCurrent Server Information:\t\t\t\t\t    |\n" );
            printf( "|\t\tIP Address: %s\t\t\t\t\t    |\n", server_ip );
            printf( "|\t\tPort Number: %d\t\t\t\t\t    |\n", port_num );
            printf( "|\t\t\t\t\t\t\t\t\t    |\n" ); 
            printf( "-----------------------------------------------------------------------------\n\n" );
            continue;
        }

        /* Send the message to the Server */
        int send_rv = sendto( socket_fd, buffer, strlen(buffer), 0, (const struct sockaddr *) &server_addr, server_len );
        if ( send_rv == -1 ) {       //Check that the message was sent successfully
            fprintf(stderr, "Failed to send the message, exiting\n");
            break;
        }

        /* Receive and store Server response */
        int rec_rv = recv( socket_fd, response_buffer, data_size, 0 );
        if ( rec_rv == -1 ) {
            fprintf(stderr, "Failed to receive response, exiting\n");
            break;
        }
        printf( "The server responded with: %s", response_buffer );     //Print the server response

        /* Clear the Server response buffer */
        int i;
        for( i = 0; i < data_size; i++ ){
            response_buffer[i] = '\0';
        }
    }

    /* Free Buffers  */
    free( buffer );
    free( response_buffer );

    close( socket_fd );     //Close the socket
}

/*
 * Function: initialize_server_address
 *
 * Purpose:
 * creates new sockaddr_in struct to hold the server's address info,
 * then takes parameter server_addr and copies the data into it
 *
 * Parameters:
 *  | server_ip     string/char* representation of the server's IPv4 address
 *  | server_addr   pointer to a sockaddr_in struct to populate
 *  | port_num      int representation of the server's port number
 *
 * Notes:
 * This function populates an existing sockaddr_in struct
 *
 * Returns:
 *  None
 */
void initialize_server_address( char *server_ip, struct sockaddr_in *server_addr, int port_num ){
    struct sockaddr_in *ret = malloc( sizeof( struct sockaddr_in ) );     //declare and allocate temporary server address struct

    ret->sin_family = AF_INET;   //Initialize socket family
    ret->sin_port = htons( port_num );   //Initialize socket port number
    inet_pton( AF_INET, server_ip, &( ret->sin_addr.s_addr ) );  //initialize IP address from char array

    memcpy( server_addr, ret, sizeof( struct sockaddr_in ) );
    free( ret );
}

/*
 * Function: get_user_message
 *
 * Purpose:
 * Gets input from stdin and populates a char array with the input.
 * Ensures correct input size and structure
 *
 * Parameters:
 *  | buffer            pointer to the char array that holds the message
 *  | buffer_size       the maximum size of the message(number of chars in the buffer)
 *
 * Notes:
 * This function returns an integer exit status of -1(failure) or 0(success)
 *
 * Returns:
 *  | 0     success
 *  | -1    failure
 */
int get_client_message( char **buffer, int buffer_size ){
    char temp_buffer[buffer_size];   //allocate temporary buffer to hold the user input

    /* Prompt user for input */
    printf( "Enter your message > " );

    /* Read user input into temporary buffer */
    if( fgets( temp_buffer, buffer_size, stdin ) == NULL ){  //Get and check that input was successful
        return -1;   //return failure exit-status
    }
    temp_buffer[ strlen( temp_buffer) ] = '\0';
    strncpy( *buffer, temp_buffer, buffer_size );    //Copy the temporary input buffer to the message buffer to be sent
    
    return 0;   //return success exit-status
}
