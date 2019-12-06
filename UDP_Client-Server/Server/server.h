/*
 * server.h
 * Author: Jackson Dumas(llt190)
 *
 * Purpose:
 *  Contains definitions of Server functionality.
 *  Server functionality includes: listening for messages, evaluating messages and
 *  responding to messages
 *
 * Notes:
 *  header file to be associated with server.c
 */

#ifndef PROJECT3NETWORKSSERVER_SERVER_H
#define PROJECT3NETWORKSSERVER_SERVER_H

/* Include Statements */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* Function Declarations */
void execute_server( int port, int data_size );
void initialize_server_address( struct sockaddr_in *server_addr, int port_num);

#endif  //PROJECT3NETWORKS_SERVER_H
