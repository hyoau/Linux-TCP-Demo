#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#define SERVPORT 3333 /* server port */
#define BACKLOG 10 /* max link number */

int main(int argc, char** argv) {
    int sockfd, client_fd; /* sock_fd: listen socket, client_fd:data tranport socket */
    struct sockaddr_in my_addr; /* local server address */
    struct sockaddr_in remote_addr; /* remote client address */
    int sin_size;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket create failure!");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVPORT); /* htons() convert the 16bit local bytes to network bytes */
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* ip address set to INADDR_ANY, os will get local ip address automatically */
    bzero(&(my_addr.sin_zero), 8); /* keep the same size as struct sockaddr */

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) == -1) {
        perror("bind failure!");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen failure!");
        exit(1);
    }

    while (1) {
        sin_size = sizeof (struct sockaddr_in);
        if ((client_fd = accept(sockfd, (struct sockaddr *) &remote_addr, &sin_size)) == -1) {
            perror("accept failure!");
            continue;
        }
        printf("Receive from: %s\n", inet_ntoa(remote_addr.sin_addr));
        if (!fork()) {
            /* child thread */
            if (send(client_fd, "Established \n", 26, 0) == -1)
                perror("Send failure！");
            close(client_fd);
            exit(0);
        }
        close(client_fd);
    }

    return (EXIT_SUCCESS);
}

