# Linux TCP Demo

A Linux TCP socket example written in C, using C/S mode. The whole process is easy to understand.

The main statements in the code are described as follows:

## Server
1. Create socket. The program calls the socket() function, which returns a handle similar to a file descriptor, which also allocates storage space for a socket data structure. Statement:

    ```c
    socket(AF_INET,SOCK_STREAM,0);
    ```
   
   The parameter `AF_INET` indicates that the IPv4 protocol is used for communication. The parameter `SOCK_STREAM` indicates that the streaming socket, namely TCP, is used.

2. Bind port. Bind the socket to a port on the machine, and then listen requests on that port. Statement:

    ```c
    bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
    ```

    The parameter `my_addr` points to information including the local IP address and port number.

3. Listen to port. Set the socket in passive listening mode, and create an input queue for the socket. Keep service requests in this queue until the program processes them. Statement:

    ```c
    listen(sockfd,BACKLOG);
    ```

    The parameter `BACKLOG` indicates the maximum number of connections.

4. Response to the client request accept. Function `accept()` generate a new socket descriptor for the server to receive the client's connection requests. Statement:
   
    ```c
    accept(sockfd,(struct sockaddr *)&remote_addr,&sin_size);
    ```
   
	The parameter `remote_addr` is used to receive client address information. The parameter `sin_size` is used to store the length of the address.

5. Send data. This function is used to send data with a connection-oriented socket. Statement:

    ```c
    send(client_fd,’Connected! \n’,26,0);
    ```
	
	26 represents the length in bytes.

6. Close socket. Statement:

    ```c
    close(client_fd);
    ```

## Client

1. Create socket. The program calls the socket() function, which returns a handle similar to a file descriptor, which also allocates storage space for a socket data structure. Statement:

    ```c
    socket(AF_INET,SOCKET_STREAM,0);
    ```
2. Send request. Start communication with remote server. Statement: 

    ```c
    connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr));
    ```

3. Receive data. This function is used to receive data from socket. Statement: 

    ```c
    recv(sockfd,buf,MAXDATASIZE,0);
    ```

4. Close socket. Statement: 

    ```c
    close(sockfd);
    ```