CS 3873-001 TCP Client/Server README by Jackson Dumas

In order to execute the client program:
1 - change your working directory to the "client" directory
2 - compile with the following command: gcc -o client main.c client.c
3 - give yourself execute permission with one of the following commands: chmod u+x client or chmod 777 client
4 - execute the program with the following command: ./client
5 - follow the usage instructions provided by the initial prompt to stdout

In order to execute the server program:
1 - change your working directory to the "server" directory
2 - compile with the following command: gcc -pthread -o server main.c server.c
3 - give yourself execute permission with one of the following commands: chmod u+x server or chmod 777 server
4 - execute the program with the following command: ./server
5 - follow the usage instructions provided by the initial prompt to stdout

With either program, the host information is defined in main.c. In order to change the server's IP address 
or port number, just change the global definitions. They are named "SERVER_IP" and "SERVER_PORT".

***All of these instructions are based on Unix based Operating Systems. Tests were run on both MACOS 10.15 Catalina as well as Ubuntu 18.04,
compilation and execution steps may vary on other systems***