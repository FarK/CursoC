#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define IP   "127.0.0.1"
#define PORT "6060"

#define MENS_LEN 100

#define ERR_CHK(cond, mens, label)          \
	do {                                \
		if (cond) {                 \
			perror(mens);       \
			ret = EXIT_FAILURE; \
			goto label;         \
		}                           \
	} while(0)                          \

char *sockaddr2str(const struct sockaddr *saddr);

int main()
{
	int ret;
	int srv_sock, cli_sock;
	struct addrinfo hints, *ai_list;
	struct sockaddr_storage cli_addr;
	socklen_t cli_addr_len = sizeof(cli_addr);
	char *addrstr;
	char mens[MENS_LEN];
	int received;

	// Init
	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;   // AF_INET, AF_INET6, AF_UNSPEC
	hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM, SOCK_DGRAM
	hints.ai_flags    = AI_PASSIVE;

	ret = getaddrinfo(NULL, PORT, &hints, &ai_list);
	ERR_CHK(ret != 0, "getaddrinfo", error);

	// Socket
	srv_sock = socket(ai_list->ai_family, ai_list->ai_socktype,
			  ai_list->ai_protocol);
	ERR_CHK(srv_sock == -1, "socket", error_free);

	// Bind
	ret = bind(srv_sock, ai_list->ai_addr, ai_list->ai_addrlen);
	ERR_CHK(ret == -1, "bind", error_free);

	// Listen
	ret = listen(srv_sock, 0);
	ERR_CHK(ret == -1, "listen", close_srv);

	addrstr = sockaddr2str(ai_list->ai_addr);
	printf("Running server on %s:%s\n", addrstr, PORT);
	free(addrstr);

	// Accept
	cli_sock = accept(srv_sock, (struct sockaddr *)&cli_addr, &cli_addr_len);
	ERR_CHK(cli_sock == -1, "accept", close_cli);

	addrstr = sockaddr2str((struct sockaddr *)&cli_addr);
	printf("Client %s is connected\n", addrstr);
	free(addrstr);

	// Receive
	do {
		received = recv(cli_sock, mens, MENS_LEN, 0);
		ERR_CHK(received == -1, "recv", close_cli);
		printf("%s", mens);
	} while (received != 0 && strcmp(mens, "exit") != 0);

	// Exit
	ret = EXIT_SUCCESS;
close_cli:
	close(cli_sock);
close_srv:
	close(srv_sock);
error_free:
	freeaddrinfo(ai_list);
error:
	return ret;
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
