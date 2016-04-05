#include "talk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define IP   "127.0.0.1"
#define PORT "6060"

#define ERR_CHK(cond, mens, label)          \
	do {                                \
		if (cond) {                 \
			perror(mens);       \
			ret = EXIT_FAILURE; \
			goto label;         \
		}                           \
	} while(0)                          \

char *sockaddr2str(const struct sockaddr *saddr);
int srv_run(const char *ip, const char *port);
int srv_accept(int listen_sock);

int main()
{
	int ret;
	int listen_sock, cli_sock;

	listen_sock = srv_run(NULL, PORT);
	ERR_CHK(listen_sock == -1, "srv_run", error);

	cli_sock = srv_accept(listen_sock);
	ERR_CHK(cli_sock == -1, "srv_accept", close_srv);

	ret = talk(cli_sock);
	ERR_CHK(!ret, "talk", close_cli);

	// Exit
	ret = EXIT_SUCCESS;
close_cli:
	close(cli_sock);
close_srv:
	close(listen_sock);
error:
	return ret;
}

int srv_run(const char *ip, const char *port)
{
	int ret;
	int listen_sock;
	struct addrinfo hints, *ai_list;
	char *addrstr;

	// Init
	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;   // AF_INET, AF_INET6, AF_UNSPEC
	hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM, SOCK_DGRAM
	hints.ai_flags    = AI_PASSIVE;

	ret = getaddrinfo(ip, port, &hints, &ai_list);
	ERR_CHK(ret != 0, "getaddrinfo", error);

	// Socket
	listen_sock = socket(ai_list->ai_family, ai_list->ai_socktype,
			     ai_list->ai_protocol);
	ERR_CHK(listen_sock == -1, "socket", error_free);

	// Bind
	ret = bind(listen_sock, ai_list->ai_addr, ai_list->ai_addrlen);
	ERR_CHK(ret == -1, "bind", error_free);

	// Listen
	ret = listen(listen_sock, 0);
	ERR_CHK(ret == -1, "listen", close_srv);

	addrstr = sockaddr2str(ai_list->ai_addr);
	ERR_CHK(!addrstr, "OOM", close_srv);
	printf("Running server on %s:%s\n", addrstr, PORT);
	free(addrstr);

	freeaddrinfo(ai_list);
	return listen_sock;
close_srv:
	close(listen_sock);
error_free:
	freeaddrinfo(ai_list);
error:
	return -1;
}

int srv_accept(int listen_sock)
{
	int ret;
	int cli_sock;
	struct sockaddr_storage cli_addr;
	socklen_t cli_addr_len = sizeof(cli_addr);
	char *addrstr;

	cli_sock = accept(listen_sock,
			(struct sockaddr *)&cli_addr,
			&cli_addr_len);
	ERR_CHK(cli_sock == -1, "accept", error);

	addrstr = sockaddr2str((struct sockaddr *)&cli_addr);
	ERR_CHK(!addrstr, "OOM", close_cli);
	printf("Client %s is connected\n", addrstr);
	free(addrstr);

	return cli_sock;
close_cli:
	close(cli_sock);
error:
	return -1;
}

char *sockaddr2str(const struct sockaddr *saddr)
{
	char *str;
	socklen_t len;
	void *addr;

	if (saddr->sa_family == AF_INET) {
		len = INET_ADDRSTRLEN;
		addr = &((struct sockaddr_in *)saddr)->sin_addr;
	} else if (saddr->sa_family == AF_INET6) {
		len = INET6_ADDRSTRLEN;
		addr = &((struct sockaddr_in6 *)saddr)->sin6_addr;
	}
	else
		return NULL;

	str = (char *)malloc(len);
	if (!str)
		return NULL;

	if (!inet_ntop(saddr->sa_family, addr, str, len)) {
		free(str);
		return NULL;
	}

	return str;
}
