/*
 * CS 3873-001 TCP Client
 * author: Jackson Dumas
 *
 * client.c
 *
 * Purpose:
 *  Contains implementation of Client functionality.
 *  Client functionality includes: connecting to server,
 *  sending message to server, receiving server response
 *
 * Driver Program:
 * main.c (Client)
 *
 * Notes:
 *  None
 */

#include "./client.h"

/*
 * Function: execute_client
 *
 * Purpose:
 * Calls helper functions to initialize all necessary server data,
 * also implements sending and receiving data to/from the server described in the arguments
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
 *      0   |   exited the client successfully
 *      1   |   exited the client unsuccessfully
 *
 * Notes:
 *  This function is called in main.c, where unrelated functionality
 *  is also called(such as the initial usage prompt)
 */
int execute_client( char *server_ip, int port, int data_size ){

    /* Variable declarations */
    int client_socket_sd;       //Socket file descriptor
    struct sockaddr_in server_addr;     //Server information
    ssize_t bytes_sent = 0, bytes_received = 0;     //return value for send() and recv() calls
    char *message_buffer = ( char * )malloc( data_size * sizeof( char ) );       //buffer to hold user input
    char response_buffer[data_size];    //buffer to hold the server response

    /* Create and validate client socket */
    if( ( client_socket_sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ){
        fprintf( stderr, "Error creating socket\n" );
        return 1;
    }

    /* Initialize server information */
    if( ( initialize_server_address( &server_addr, server_ip, port ) ) == -1 ){
        fprintf( stderr, "Error initializing server\n" );
        return 1;
    }

    /* Connect to the server */
    if( connect( client_socket_sd, (struct sockaddr *)&server_addr, ( socklen_t )sizeof( server_addr ) ) != 0 ){
        fprintf( stderr, "Error connecting to server\n" );
        return 1;
    }

    /* User input loop */
    while( 1 ){

        /* Get Client message */
        if ( get_client_message( &message_buffer, data_size ) != 0 || strlen( message_buffer ) <= 1 ) {
            fprintf(stderr, "Failed to get a valid message, exiting\n");
            return 1;
        }
        /* Check for commands */
        if ( strcmp( message_buffer, ".exit\n" ) == 0 ){        //exit the program
            printf( "Exiting the client\n" );
            break;
        }else if ( strcmp( message_buffer, ".print\n" ) == 0 ){     //print the server info
            printf( "\nCurrent Server Information:\n" );
            printf( "\tIP Address: %s\n", server_ip );
            printf( "\tPort Number: %d\n", port ); 
            printf( "\t-------------------------------------------\n\n" );
            continue;
        }

        /* Send message to the server */
        bytes_sent = send( client_socket_sd, message_buffer, strlen( message_buffer ) + 1, 0 );
        if( bytes_sent != strlen( message_buffer ) + 1 ){
            fprintf( stderr, "Error sending message to server\n" );
            return 1;
        }

        /* Receive server response */
        bytes_received = recv( client_socket_sd, response_buffer, sizeof( response_buffer ), 0 );
        if( bytes_received < 0 ){
            fprintf( stderr, "Error receiving a server response\n" );
            return 1;
        }

        /* Print the server response */
        printf( "The server responded with: %s\n", response_buffer );

        /* Clear the response buffer */
        int i;
        for( i = 0; i < data_size; i++ ){
            response_buffer[i] = '\0';
        }
    }

    /* Close the socket and end client */
    close( client_socket_sd );
    free( message_buffer );
    return 0;
}

/*
 * Function: initialize_server_address
 *
 * Purpose:
 * creates new sockaddr_in struct to hold the server's address info,
 * then copies the new sockaddr_in into the passed sockaddr_in struct's memory
 *
 * Parameters:
 *  | server_addr   the server address struct to overwrite with an initialized sockaddr_in struct
 *  | port_num      int representation of the server's port number
 *
 * Notes:
 * This function returns a pointer to a sockaddr_in struct describing the server
 *
 * Returns:
 *      0 |   initialized sockaddr_in struct -> success
 *      -1 |   could not initialize sockaddr_in struct -> failure
 */
int initialize_server_address( struct sockaddr_in *server_addr, char *server_ip, int port_num ) {
    struct sockaddr_in *ret = malloc( sizeof( struct sockaddr_in ) );     //declare and allocate temporary server address struct
    if( ret == NULL ){      //Check if malloc was successful
        return -1;
    }

    ret->sin_family = AF_INET;   //Initialize socket family
    ret->sin_port = htons( port_num );   //Initialize socket port number
    inet_pton( AF_INET, server_ip, &( ret->sin_addr.s_addr ) );  //initialize IP address from char array

    memcpy( server_addr, ret, sizeof( struct sockaddr_in ) );       //copy the temporary sockaddr_in into the first argument's memory
    free( ret );        //free the temporary struct
    return 0;
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
    memcpy( *buffer, temp_buffer, buffer_size );    //Copy the temporary input buffer to the message buffer to be sent

    return 0;   //return success exit-status
}
