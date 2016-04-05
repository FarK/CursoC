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

#define PORT "6060"
#define IP   "127.0.0.1"

#define ERR_CHK(cond, mens, label)          \
	do {                                \
		if (cond) {                 \
			perror(mens);       \
			ret = EXIT_FAILURE; \
			goto label;         \
		}                           \
	} while(0)                          \

char *sockaddr2str(const struct sockaddr *saddr);
int cli_connect(const char *ip, const char *port);

int main()
{
	int ret;
	int srv_sock;

	srv_sock = cli_connect(IP, PORT);
	ERR_CHK(srv_sock == -1, "cli_connect", error);

	ret = talk(srv_sock);
	ERR_CHK(!ret, "talk", close);

	// Exit
	ret = EXIT_SUCCESS;
close:
	close(srv_sock);
error:
	return ret;
}

int cli_connect(const char *ip, const char *port)
{
	int ret;
	int srv_sock;
	struct addrinfo hints, *ai_list;
	char *addrstr;

	// Init
	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;   // AF_INET, AF_INET6, AF_UNSPEC
	hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM, SOCK_DGRAM

	ret = getaddrinfo(ip, port, &hints, &ai_list);
	ERR_CHK(ret != 0, "getaddrinfo", error);

	addrstr = sockaddr2str(ai_list->ai_addr);
	ERR_CHK(!addrstr, "OOM", error_free);
	free(addrstr);

	// Socket
	srv_sock = socket(ai_list->ai_family, ai_list->ai_socktype,
			  ai_list->ai_protocol);
	ERR_CHK(srv_sock == -1, "socket", error_free);

	// Connect
	ret = connect(srv_sock, ai_list->ai_addr, ai_list->ai_addrlen);
	ERR_CHK(ret == -1, "connect", close);

	freeaddrinfo(ai_list);
	return srv_sock;
close:
	close(srv_sock);
error_free:
	freeaddrinfo(ai_list);
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
