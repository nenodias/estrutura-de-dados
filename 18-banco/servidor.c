// #include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PROCESS 5
#define MAX_BUFFER 80
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

// SERVIDOR
int init_server(TServidor *servidor)
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
    bzero(&servidor->socket, sizeof(struct sockaddr_in));

    // assign IP, PORT
    servidor->socket.sin_family = AF_INET;
    servidor->socket.sin_addr.s_addr = htonl(INADDR_ANY);
    servidor->socket.sin_port = htons(PORT);
    servidor->sockfd = sockfd;
    return sockfd;
}

void binding(TServidor *servidor)
{
    // Binding newly created socket to given IP and verification
    int len = sizeof(struct sockaddr_in);
    int bind_return = bind(servidor->sockfd, (SA *)&servidor->socket, len);
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

void listening(TServidor *servidor)
{
    // Now server is ready to listen and verification
    if ((listen(servidor->sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }
}

int accept_connections(TConexao *servidor)
{
    int len = sizeof(struct sockaddr_in);
    // Accept the data packet from client and verification
    int connfd = accept(servidor->sockfd, (SA *)servidor->cli, &len);
    if (connfd < 0)
    {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
    {
        printf("server acccept the client...\n");
    }
    servidor->connfd = connfd;
    return connfd;
}

void deal_connections(TConexao *servidor)
{
    accept_connections(servidor);
    process(servidor->connfd);
    printf("Finalizou conexao %d\n", servidor->connfd);
}

// BUSINESS

struct TConta
{
    int numero;
    char nome[50];
    float valor;
};
typedef struct TConta TConta;

void saldo(TConta *conta)
{
    printf("OPERACAO: SALDO -> [%d, %s, %.2f]\n", conta->numero, conta->nome, conta->valor);
}

int sacar(TConta *conta, float valor)
{
    printf("OPERACAO: SAQUE -> [%d, %s, %.2f] - %.2f\n", conta->numero, conta->nome, conta->valor, valor);
    if (valor >= 0 && conta->valor >= valor)
    {
        conta->valor -= valor;
        printf("OPERACAO: SAQUE -> [%d, %s, %.2f] - OK\n", conta->numero, conta->nome, conta->valor);
        return 1;
    }
    printf("OPERACAO: SAQUE -> [%d, %s, %.2f] - NEGADA\n", conta->numero, conta->nome, conta->valor);
    return 0;
}

int depositar(TConta *conta, float valor)
{
    printf("OPERACAO: DEPOSITO -> [%d, %s, %.2f] - %.2f\n", conta->numero, conta->nome, conta->valor, valor);
    if (valor >= 0)
    {
        conta->valor += valor;
        printf("OPERACAO: DEPOSITO -> [%d, %s, %.2f] - OK\n", conta->numero, conta->nome, conta->valor);
        return 1;
    }
    printf("OPERACAO: DEPOSITO -> [%d, %s, %.2f] - NEGADA\n", conta->numero, conta->nome, conta->valor);
    return 0;
}

// PROCESS

void process(int sockfd)
{
    char buff[MAX_BUFFER];
    int n;
    // infinite loop for chat
    for (;;)
    {
        bzero(buff, MAX_BUFFER);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        int numero = atoi(buff);
        printf("Numero: %d\n", numero);
        if (numero >= 0 && numero < MAX_PROCESS)
        {
        }
        else
        {
            strcpy(buff, "Conta invalida\0");
            write(sockfd, buff, sizeof(buff));
            bzero(buff, MAX_BUFFER);
            break;
        }

        // print buffer which contains the client contents
        printf("From client: %s", buff);
        bzero(buff, MAX_BUFFER);
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

// MUTEX
pthread_mutex_t mutex_conta;

TConta contas[MAX_PROCESS] = {
    {1, "Cliente 1\0", 100},
    {2, "Cliente 2\0", 150},
    {3, "Cliente 3\0", 200},
    {4, "Cliente 4\0", 250},
    {5, "Cliente 5\0", 0},
};

int main()
{
    // if(!sacar(&conta, 120)){
    //     if(depositar(&conta, 120)){
    //         saldo(&conta);
    //         sacar(&conta, 120);
    //         saldo(&conta);
    //     }
    // }

    // SERVER
    int connfd[MAX_PROCESS];
    struct sockaddr_in server, cli[5];
    TServidor *servidor = (TServidor *)malloc(sizeof(TServidor));
    servidor->sockfd = 0;
    TConexao *conexoes[MAX_PROCESS] = {NULL, NULL, NULL, NULL, NULL};

    init_server(servidor);
    binding(servidor);
    listening(servidor);

    pthread_t workers[MAX_PROCESS];
    pthread_mutex_init(&mutex_conta, NULL);

    while (1)
    {
        for (int i = 0; i < MAX_PROCESS; i++)
        {
            printf("Criando conexao %d\n", i);
            conexoes[i] = (TConexao *)malloc(sizeof(TConexao));
            conexoes[i]->connfd = 0;
            conexoes[i]->sockfd = servidor->sockfd;
            conexoes[i]->cli = &cli[i];
            printf("Criando thread conexao %d\n", conexoes[i]->connfd);
            pthread_create(&workers[i], NULL, deal_connections, (void *)conexoes[i]);
        }
        for (int i = 0; i < MAX_PROCESS; i++)
        {
            printf("Join thread %d\n", i);
            if (workers[i] != NULL)
            {
                pthread_join(workers[i], NULL);
                printf("Join conexao %d\n", i);
                free(conexoes[i]);
                conexoes[i] = NULL;
            }
        }
    }
    // After chatting close the socket
    close(servidor->sockfd);
    return 0;
}