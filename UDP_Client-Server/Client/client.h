/*
 * CS 3873-001 UDP Client
 * author: Jackson Dumas
 *
 * client.h
 *
 * Purpose:
 *  Contains definitions of Client functionality.
 *  Client functionality includes: connecting to server, sending UDP datagram,
 *  receiving server response, responding to server response
 *
 * Notes:
 *  header file to be associated with client.c
 */

#ifndef PROJECT3NETWORKS_CLIENT_H
#define PROJECT3NETWORKS_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* Function Declarations */
void execute_client( char *server_ip, int port, int data_size ); //Client driver, calls all other helper functions
void initialize_server_address( char *server_ip, struct sockaddr_in *server_addr, int port_num );     //Initializes the server address data
int get_client_message( char **buffer, int buffer_size );   //Gets user input and returns char array with correct size

#endif