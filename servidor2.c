//=============================================================================
// Tarefa 07 - Servidor de comandos (TCP) - Programa Servidor
// Autor: Tiago Guerino de Oliveira Bassani RA:0040481722003
//=============================================================================

#include "./local.h"

int main(int argc, char * argv[])
{
	int socket_servidor, socket_cliente, tamanho_socket, bytes_recebidos;
	struct sockaddr_in cliente;
	struct sockaddr_in servidor;
	char buffer[MAX_SIZE_BUFFER];

	tamanho_socket = sizeof(struct sockaddr_in);

	socket_servidor = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servidor, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(PORT);
	servidor.sin_addr.s_addr = INADDR_ANY;

	bind(socket_servidor, (struct sockaddr *)&servidor, sizeof(servidor));

	struct utsname uts;
	uname(&uts);

	listen(socket_servidor, 1);

	printf("Servidor aguardando mensagens na porta %d\n", PORT);

	while (1)
	{
		socket_cliente = accept(socket_servidor, (struct sockaddr *)&cliente, &tamanho_socket);

		bytes_recebidos = recv(socket_cliente, buffer, MAX_SIZE_BUFFER, 0);
		buffer[bytes_recebidos] = '\0';
		FILE *arq;
		arq = fopen("log.txt", "a");
		char data[11], hora[9];

		time_t rawtime;
		struct tm *info;

		time(&rawtime);
		info = localtime(&rawtime);
		strftime(data, MAX_SIZE_BUFFER, "%d/%m/%Y", info);
		strftime(hora, MAX_SIZE_BUFFER, "%X", info);

		fprintf(arq, "---------------------------------------------------");
		fprintf(arq, "|%s|%s|%s|\n", data, hora, buffer);

		if (!strcmp(buffer, "date")) {
			strcpy(buffer, data);
		}
		else if (!strcmp(buffer, "time")) {
			strcpy(buffer, hora);
		}
		else if (!strcmp(buffer, "nodename")) {
			strcpy(buffer, uts.nodename);
		}
		else if (!strcmp(buffer, "sysname")) {
			strcpy(buffer, uts.sysname);
		}
		else if (!strcmp(buffer, "release")) {
			strcpy(buffer, uts.release);
		}
		else if (!strcmp(buffer, "version")) {
			strcpy(buffer, uts.version);
		}
		else if (!strcmp(buffer, "machine")) {
			strcpy(buffer, uts.machine);
		}
		else if (!strcmp(buffer, "shutdown")) { 
			break; 
		}
		else if (!strcmp(buffer, "credits")) { 
			strcpy(buffer, "Tiago Guerino de Oliveira Bassani\nRA: 0040481722003");
		}
		else { 
			strcpy(buffer, "Comando Não encontrado ou Inválido!");
		}

		send(socket_cliente, buffer, MAX_SIZE_BUFFER, 0);

		fclose(arq);
	}
	close(socket_cliente);	
	close(socket_servidor);
	sleep(1);
	printf("Servidor encerrado.");
	return 0;
}

