#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3001
#define BUFFER_LENGTH 4096
#define SERVER_ADDR "127.0.0.1"

int main(void)
{
    struct sockaddr_in server;

    int sockfd;

    char buffer_in[BUFFER_LENGTH];
    char buffer_out[BUFFER_LENGTH];
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == !0)
    {
        perror("\nErro ao criar o socket do cliente: ");
        exit(EXIT_FAILURE);
    }
    printf("\nCliente conectado!\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    int server_len = sizeof(server);
    if(connect(sockfd, (struct sockaddr*) &server, server_len) == !0)
    {
        perror("\nErro ao se conectar ao servidor: ");
        exit(EXIT_FAILURE);
    }
    printf("Conexão com o servidor estabelecida!\n");

    if(recv(sockfd, buffer_in, BUFFER_LENGTH, 0) > 0)
    {
        printf("\n%s",buffer_in);
    }

    do
    {
        memset(buffer_in, 0, BUFFER_LENGTH);
        memset(buffer_out, 0, BUFFER_LENGTH);

        printf("Insira o nome de algum arquivo: ");
        fgets(buffer_out, BUFFER_LENGTH, stdin);

        send(sockfd, buffer_out, strlen(buffer_out), 0);
        recv(sockfd, buffer_in, BUFFER_LENGTH, 0);
        printf("\n%s\n\n", buffer_in);

    } while (strcmp(buffer_in, "Volte sempre!"));
    
    close(sockfd);
    printf("Conexão encerrada!\n\n");
    return(EXIT_SUCCESS);
}
