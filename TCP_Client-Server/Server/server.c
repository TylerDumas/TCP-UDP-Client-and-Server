/*
 * CS 3873-001 TCP Server
 * author: Jackson Dumas
 *
 * server.c
 *
 * Purpose:
 * The Server portion of the Client/Server TCP program.
 * Implements socket programming to receive and respond to messages sent by a client
 *
 * Notes:
 *  Almost all functionality for the server is implemented in this source file
*/

#include "./server.h"

/*
 * Function: execute_server
 * Contains all functionality for executing the server program.
 * Calls on all helper functions to listen for messages and accept TCP connection requests
 * returns an integer exit status
 *
 * Param: server_ip |   char array holding this server's IP address
 * Param: port_num  |   integer representation of this server's port number(that is accepting TCP connections)
 * Param: data_size |   integer representation of the maximum number of characters to be sent and received
 *
 * Returns:
 *      0   |   exited the server successfully
 *      1   |   exited the server unsuccessfully
 *
 * Notes:
 *  This function is called in main, where unrelated functionality
 *  is also called(such as the initial prompt)
 */
int execute_server( char *server_ip, int port_num, int data_size ){
    /* Variable Declarations */
    int initial_socket_sd, new_socket_sd;       //Socket file descriptors for initial socket and socket for new connections
    struct sockaddr_in server_addr;    //Structs to hold host information
    struct sockaddr_in client_addr;     //to store client address information
    socklen_t client_addr_len;       //length of the client sockaddr_in struct
    pthread_t thread_id;        //Thread id for use in multi-threading
    thread_args *t_args;        //thread_args struct to hold parameters for thread function

    /* Initialize initial socket */
    initial_socket_sd = socket( AF_INET, SOCK_STREAM, 0 );
    if( initial_socket_sd == -1 ){
        fprintf( stderr, "Could not create the initial server socket\n" );
        return 1;
    }

    /* Initialize server address struct with correct information */
    if( ( initialize_server_address( &server_addr, server_ip, port_num ) ) == -1 ){
        fprintf( stderr, "Could not initialize server information\n" );
        return 1;
    }

    /* Bind the initial socket with server_addr */
    if ( ( bind( initial_socket_sd, (struct sockaddr *)&server_addr, sizeof( server_addr ) ) ) < 0 ){
        fprintf( stderr, "Failed to bind to initial socket\n" );
        return 1;
    }

    /* Listen on initial socket with a maximum N connections queued */
    if( listen( initial_socket_sd, 5 ) == 0 ){      //The server is listening successfully
        printf( "Listening for an incoming TCP connection...\n\n" );
    }else{      //The server has stopped listening
        fprintf( stderr, "The server stopped listening unexpectedly\n" );
        return 1;
    }

    /* Loop while accepting the client connection */
    while( 1 ){

        client_addr_len = sizeof( client_addr );        //Initialize the client_addr size

        /* Accept a new TCP connection request */
        new_socket_sd = accept( initial_socket_sd, (struct sockaddr *)&client_addr, &client_addr_len );

        /* Check if new socket was created successfully */
        if( new_socket_sd == -1 ){      //Check if new socket was created successfully
            fprintf( stderr, "Could not create new server socket\n" );
            break;
        }

        /* Create new thread_args struct and initialize it */
        t_args = (thread_args *)malloc( sizeof( thread_args ) );
        t_args->socket_sd = new_socket_sd;
        t_args->return_value = 0;
        t_args->data_size = data_size;

        /* Create thread for the new socket */
        if( ( pthread_create( &thread_id, NULL, connection_handler, (void *)t_args ) ) < 0 ){
            fprintf( stderr, "Could not create new thread\n" );
            return 1;
        }

        /* Alert user of new connection */
        printf( "New connection accepted from address: %s\n", inet_ntoa( client_addr.sin_addr ) );
    }

    /* Close the initial socket */
    close( initial_socket_sd );
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
 *     !0 |   could not initialize sockaddr_in struct -> failure
 */
int initialize_server_address( struct sockaddr_in *server_addr, char *server_ip, int port_num ) {
    struct sockaddr_in *ret = malloc( sizeof( struct sockaddr_in ) );     //declare and allocate temporary server address struct
    if( ret == NULL ){      //Check if malloc was successful
        return 1;
    }

    ret->sin_family = AF_INET;   //Initialize socket family
    ret->sin_port = htons( port_num );   //Initialize socket port number
    inet_pton( AF_INET, server_ip, &( ret->sin_addr.s_addr ) );  //initialize IP address from char array

    memcpy( server_addr, ret, sizeof( struct sockaddr_in ) );
    free( ret );
    return 0;
}

/*
 * Function: connection_handler
 * Receives and responds to messages from the newly created socket
 * Takes messages that are received and sends them back to the host that sent them
 *
 * param: new_socket_ptr    |   pointer to the newly created socket(the new TCP connection)
 *
 * returns: void pointer
 */
void* connection_handler( void *t_args ){
    int bytes_received, bytes_sent;     //return values for recv and send calls
    thread_args *thread_info = (thread_args *)t_args;
    char message[thread_info->data_size];   //buffer to hold message

    /* Loop until the client disconnects */
    while( 1 ){

        /* Receive client messages */
        bytes_received = recv( thread_info->socket_sd , message, thread_info->data_size, 0 );
        if( bytes_received > 0 ){       //message was received
            printf( "The client said: %s\n", message );
        }else{      //Message was not received
            printf( "Client disconnected\n" );
            close( thread_info->socket_sd );        //close the client socket
            free( t_args );
            break;
        }

        /* Send Response back to client */
        bytes_sent = send( thread_info->socket_sd, message, strlen( message ) + 1, 0 );
        if( bytes_sent != strlen( message ) + 1 ){
            fprintf( stderr, "Error sending response\n" );
            close( thread_info->socket_sd );
            free( t_args );
            break;
        }
    }
    return NULL;
}
