/*
 * CS 3873-001 TCP Server
 * author: Jackson Dumas
 *
 * server.h
 *
 * Purpose:
 * The header file to declare all functions and dependencies for server.c
 *
*/

#ifndef PROJ4SERVER_SERVER_H
#define PROJ4SERVER_SERVER_H

/* Include statements */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

/* Function Declarations */
int execute_server( char *server_ip, int port, int data_size );
int initialize_server_address( struct sockaddr_in *server_addr, char *server_ip, int port_num );
void* connection_handler( void *new_socket_ptr );

/* Struct Definitions */

typedef struct{     //Struct to define the parameters for a new thread
    int socket_sd;
    int return_value;
    int data_size;
}thread_args;

#endif //PROJ4SERVER_SERVER_H
