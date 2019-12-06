/*
 * CS 3873-001 TCP Client
 * author: Jackson Dumas
 *
 * client.h
 *
 * Purpose:
 * The header file to declare all functions and dependencies for client.c
 *
*/

#ifndef PROJ4CLIENT_CLIENT_H
#define PROJ4CLIENT_CLIENT_H

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
int execute_client( char *server_ip, int port, int data_size ); //Client driver, calls all other helper functions
int initialize_server_address( struct sockaddr_in *server_addr, char *server_ip,  int port_num );     //Initializes the server address data
int get_client_message( char **buffer, int buffer_size );   //Gets user input and returns char array with correct size

#endif //PROJ4CLIENT_CLIENT_H
