//=============================================================================
// Tarefa 07 - Servidor de comandos (TCP) - Programa Cliente
// Autor: Tiago Guerino de Oliveira Bassani RA:0040481722003
//=============================================================================

#include "./local.h"

int main(int argc, char * argv[])
{
	int socket_servidor, bytes_recebidos;
	struct sockaddr_in servidor;
	char buffer[MAX_SIZE_BUFFER];

	while (1) {
		printf("Insira um comando: ");
		gets(buffer);
		if (!strcmp(buffer, "exit")) {
			break;
		}
		else if (!strcmp(buffer, "help") {
			printf("----------------------------------------------------------------------\n");
			printf("date: (r) retornar a data\n");
			printf("time: (r) retornar a hora\n");
			printf("nodename: (r) retornar o nome do nó\n");
			printf("release: (r) retornar a liberação do sistema\n");
			printf("version: (r) retornar a versão do sistema\n");
			printf("machine: (r) retornar o nome da maquina\n");
			printf("shutdown: (rl) encerrar a execução das aplicações CLIENTE e SERVIDOR\n");
			printf("credits: (r) exibir o nome completo de todos os participantes da equipe\n");
			printf("exit: (l) encerrar a execução da aplicação CLIENTE\n");
			printf("help: (l) exibir um auxílio sobre os comandos existentes\n");
			printf("----------------------------------------------------------------------\n");
		}
		else {
			socket_servidor = socket(AF_INET, SOCK_STREAM, 0);

			bzero(&servidor, sizeof(servidor));
			servidor.sin_family = AF_INET;
			servidor.sin_port = htons(PORT);
			inet_aton(argv[1], &servidor.sin_addr.s_addr);

			connect(socket_servidor, (struct sockaddr*)&servidor, sizeof(servidor));

			send(socket_servidor, buffer, MAX_SIZE_BUFFER, 0);
			if (!strcmp(buffer, "shutdown")) {
				break;
			}
			bytes_recebidos = recv(socket_servidor, buffer, MAX_SIZE_BUFFER, 0);
			printf("%s\n", buffer);
		}
	}
	close(socket_servidor);
	sleep(1);
	printf("Cliente encerrado.");
	return 0;
}

