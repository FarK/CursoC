#include "talk.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>

#define MENS_LEN 100

static bool g_cont = true;

void exit_hdl(int signal);
int receive_frk(int cli_sock);
int send_frk(int cli_sock);

int talk(int sock)
{
	int ret;
	int pid;
	struct sigaction sa;

	// Signal config
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = exit_hdl;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		return 0;
	if (sigaction(SIGTERM, &sa, NULL) == -1)
		return 0;

	pid = fork();
	if (pid == -1)
		return 0;


	// Child
	if (pid == 0) {
		ret = receive_frk(sock);
		if (ret && errno != EINTR)
			printf("El interlocutor se desconectó\n");
	// Parent
	} else {
		ret = send_frk(sock);
		int saved_errno = errno;
		if (waitpid(-1, NULL, WNOHANG) == 0) // Si el hijo está vivo
			kill(pid, SIGTERM);          // Lo matamos antes de salir
		errno = saved_errno;
	}

	return ret;
}

int receive_frk(int sock)
{
	char mens[MENS_LEN];
	int received;

	do {
		received = recv(sock, mens, MENS_LEN, 0);
		if (received == -1)
			return errno == EINTR? 1 : 0;
		printf(">> %s", mens);
	} while (g_cont && received != 0);

	return 1;
}

int send_frk(int sock)
{
	char mens[MENS_LEN] = "";
	int sent;

	while (g_cont && strcmp(mens, "quit\n") != 0)
	{
		if (!fgets(mens, MENS_LEN, stdin))
			return errno == EINTR? 1 : 0;
		sent = send(sock, mens, MENS_LEN, 0);
		if (sent != MENS_LEN)
			return 0;
	}

	return 1;
}

void exit_hdl(int signal)
{
	g_cont = false;
}
