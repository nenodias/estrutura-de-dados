#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

struct TServidor
{
    int sockfd;
    struct sockaddr_in socket;
};
typedef struct TServidor TServidor;

struct TConexao
{
    int sockfd;
    int connfd;
    struct sockaddr_in *cli;
};
typedef struct TConexao TConexao;

int init_server(TServidor *servidor)
{
    // socket create and varification
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
    bzero(&servidor->socket, sizeof(struct sockaddr_in));

    // assign IP, PORT
    servidor->socket.sin_family = AF_INET;
    servidor->socket.sin_addr.s_addr = inet_addr("127.0.0.1");
    servidor->socket.sin_port = htons(PORT);
    servidor->sockfd = sockfd;
    return sockfd;
}

int connect_server(TServidor *servidor)
{
    SA * socket = (SA *)&servidor->socket;
    if (connect(servidor->sockfd, socket, sizeof(struct sockaddr_in)) != 0)
    {
        printf("connection with the server failed...\n");
        return 0;
    }
    else
    {
        printf("connected to the server..\n");
    }
    return 1;
}

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        char leitura[50];
        int conta;
        char operacao;
        float valor;
        bzero(buff, sizeof(buff));
        printf("Qual a sua conta: \n");
        scanf("%s", &leitura);
        conta = atoi(leitura);
        printf("Qual a operação(S/D)[Sacar/Depositar]: \n");
        scanf("%s", &operacao);
        printf("Qual o valor: \n");
        scanf("%f", &valor);
        printf("Conta: %i\nOperação: %c\nValor: %.2f\n", conta, operacao, valor);
        sprintf(buff,"%i,%c,%.2f\n",conta, operacao, valor);
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        break;
    }
}

int main()
{
    TServidor *servidor = (TServidor *)malloc(sizeof(TServidor));
    servidor->sockfd = 0;
    int sockfd, connfd;

    init_server(servidor);
    connect_server(servidor);
    
    // function for chat
    func(servidor->sockfd);

    // close the socket
    close(servidor->sockfd);
}