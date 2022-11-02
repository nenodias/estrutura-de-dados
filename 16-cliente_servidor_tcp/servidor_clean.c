#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int init_server(struct sockaddr_in *servaddr)
{
    // socket create and verification
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }
    bzero(servaddr, sizeof(struct sockaddr_in));

    // assign IP, PORT
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr->sin_port = htons(PORT);
    return sockfd;
}

void binding(int sockfd, struct sockaddr_in *servaddr)
{
    // Binding newly created socket to given IP and verification
    int len = sizeof(struct sockaddr_in);
    int bind_return = bind(sockfd, (SA *)servaddr, len);
    if (bind_return != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }
}

void listening(int sockfd)
{
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
}

int accept_connections(int sockfd, struct sockaddr_in *cli)
{
    int len = sizeof(struct sockaddr_in);
    // Accept the data packet from client and verification
    int connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
    {
        printf("server acccept the client...\n");
    }
    return connfd;
}

// Driver function
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = init_server(&servaddr);
    binding(sockfd, &servaddr);
    listening(sockfd);

    connfd = accept_connections(sockfd, &cli);

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}