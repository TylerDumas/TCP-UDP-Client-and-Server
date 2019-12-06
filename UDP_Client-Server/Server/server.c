/*
 * CS 3873-001 UDP Server
 * author: Jackson Dumas
 *
 * server.c
 *
 * Purpose:
 *  Contains definitions of Server functionality.
 *  Server functionality includes: listening for messages, evaluating messages and
 *  responding to messages
 *
 * Driver Program:
 *  main.c (server)
 *
 * Notes:
 *  None
 */

/* Include Statements */
#include "./server.h"


/*********************** Function Definitions **************************/

/*
 * Function: execute_server
 *
 * Purpose:
 * Calls helper functions to initialize all necessary server and client data,
 * also implements receiving messages from the client and responding to them
 *
 * Parameters:
 *  | server_ip     string representation of the server's IPv4 address
 *  | port_num      int representation of the server's port number
 *  | data_size     the maximum size of the data(character array) to send to the server
 *
 * Notes:
 * This function holds the majority of the functionality of the server program
 *
 * Returns:
 *  | None
 */
void execute_server( int port, int data_size ){

    int socket_fd;      //Socket file descriptor
    int client_len;     //Size of the Client address struct
    char message_buffer[data_size];     //The char array to hold the client messages

    /* Initialize Server information */
    struct sockaddr_in server_addr;
    initialize_server_address( &server_addr, port );

    /* Allocate Client information */
    struct sockaddr_in client_addr;
    client_len = sizeof( client_addr );
    memset( &client_addr, 0, sizeof( client_addr ) );

    /* Create and verify Socket */
    if ( (socket_fd = socket( AF_INET, SOCK_DGRAM ,IPPROTO_UDP ) ) < 0 ) {
        fprintf( stderr, "Failed to create the client socket\n" );
        exit( EXIT_FAILURE );
    }

    /* Bind the Socket to the Server address */
    if ( bind( socket_fd, (const struct sockaddr *)&server_addr, sizeof( server_addr ) ) < 0 ){
        fprintf( stderr, "Failed to bind to socket\n" );
        exit( EXIT_FAILURE );
    }

    /********  Server Listen/Respond loop  ********/
    while( 1 ){
        
        /* Listen for Messages */
        int rec_rv = recvfrom( socket_fd, message_buffer, data_size, 0, (struct sockaddr *)&client_addr, (socklen_t *)&client_len );
        if ( rec_rv == -1 ){        //Handle Receiving error
            fprintf( stderr, "Failed to receive message, exiting\n" );
            break;
        }
        printf( "The client sent you: %s\n\n", message_buffer );  //Print the Client's message

        /* Respond to the Message */
        int send_rv = sendto( socket_fd, message_buffer, strlen( message_buffer ), 0, (struct sockaddr *)&client_addr, client_len );
        if( send_rv == -1 ){        //Handle Responding error
            fprintf( stderr, "Failed to send response, exiting\n" );
            break;
        }

        /* Clear the message buffer */
        int i = 0;
        for( i = 0; i < data_size; i++ ){
            message_buffer[i] = '\0';
        }
    }

    close( socket_fd );     //Close the Server socket
}


/*
 * Function: initialize_server_address
 *
 * Purpose:
 * creates new sockaddr_in struct to hold the server's address info,
 * then returns pointer to the new struct
 *
 * Parameters:
 *  | server_ip     string/char* representation of the server's IPv4 address
 *  | port_num      int representation of the server's port number
 *
 * Notes:
 * This function returns a pointer to a sockaddr_in struct describing the server
 *
 * Returns:
 *  | initialized sockaddr_in struct -> success
 *  | NULL -> failure
 */
void initialize_server_address( struct sockaddr_in *server_addr, int port_num ) {
    struct sockaddr_in *ret = malloc( sizeof( struct sockaddr_in ) );     //declare and allocate temporary server address struct

    ret->sin_family = AF_INET;   //Initialize socket family
    ret->sin_port = htons( port_num );   //Initialize socket port number
    ret->sin_addr.s_addr = INADDR_ANY;      //Initialize socket address to any

    memcpy( server_addr, ret, sizeof( struct sockaddr_in ) );
    free( ret ); 
}
