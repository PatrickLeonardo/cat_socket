#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_LENGTH 4096
#define PORT 3001

int main(void)
{
    struct sockaddr_in server, client;

    int serverfd, clientfd;

    char buffer[BUFFER_LENGTH];

    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == !0)
    {
        perror("\nErro ao criar o servidor: ");
        exit(EXIT_FAILURE);
    }
    printf("\nServidor conectado!\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
 
    int value = 1;
    if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) == !0)
    {
        perror("\nErro ao redirecionar as opções: ");
        exit(EXIT_FAILURE);
    }

    if(bind(serverfd, (struct sockaddr*) &server, sizeof(server)) == !0)
    {
        perror("\nErro no bind: ");
        exit(EXIT_FAILURE);
    }

    if(listen(serverfd, 1) == !0)
    {
        perror("\nErro na listagem da porta: ");
        exit(EXIT_FAILURE);
    }
    printf("Listando na porta: %i!\n", PORT);

    socklen_t client_len = sizeof(client);
    if((clientfd = accept(serverfd, (struct sockaddr*) &client, &client_len)) == !0)
    {
        perror("\nErro no accept: ");
        exit(EXIT_FAILURE);
    }
    
    strcpy(buffer, "Seja bem vindo! (digite 'exit' para sair)\n");

    if(send(clientfd, buffer, strlen(buffer), 0))
    {
        printf("\nCliente conectado.\nEsperando por alguma mensagem ...\n\n");
        
        do
        {
            memset(buffer, 0, BUFFER_LENGTH);

            int message_len;
            if((message_len = recv(clientfd, buffer, BUFFER_LENGTH, 0)) > 0)
            {
                buffer[message_len - 1] = '\0';
                printf("Cliente diz: %s\n", buffer);
            }

            if(strstr(buffer, ".txt"))    
            {
                FILE *file;
                file = fopen(buffer, "r");
                char get[BUFFER_LENGTH];
                char content[BUFFER_LENGTH];
                while (!feof(file))
                {
                    fgets(get, BUFFER_LENGTH, file);
                    strcat(content, get);
                }
                if(send(clientfd, content, BUFFER_LENGTH, 0));
                {
                    printf("Arquivo enviado!\n\n");
                }
            }

            if(strcmp(buffer, "exit") == 0)
            {
                send(clientfd, "Volte sempre!", 13, 0);
            }

        } while (strcmp(buffer, "exit"));
    }
    
    close(serverfd);
    printf("\nConexão encerrada!\n\n");
    return(EXIT_SUCCESS); 
}
