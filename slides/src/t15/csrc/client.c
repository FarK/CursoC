#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "6060"
#define IP   "127.0.0.1"

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
	int srv_sock;
	struct addrinfo hints, *ai_list;
	char *addrstr;
	char mens[MENS_LEN];
	int sent;

	// Init
	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;   // AF_INET, AF_INET6, AF_UNSPEC
	hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM, SOCK_DGRAM

	ret = getaddrinfo(IP, PORT, &hints, &ai_list);
	ERR_CHK(ret != 0, "getaddrinfo", error);
	addrstr = sockaddr2str(ai_list->ai_addr);

	// Socket
	srv_sock = socket(ai_list->ai_family, ai_list->ai_socktype,
			  ai_list->ai_protocol);
	ERR_CHK(srv_sock == -1, "socket", error_free);

	// Connect
	ret = connect(srv_sock, ai_list->ai_addr, ai_list->ai_addrlen);
	ERR_CHK(ret == -1, "connect", close);

	// Send
	do {
		fgets(mens, MENS_LEN, stdin);
		sent = send(srv_sock, mens, MENS_LEN, 0);
		ERR_CHK(sent != MENS_LEN, "sent incomplete", close);
	} while (strcmp(mens, "exit\n") != 0);

	// Exit
	ret = EXIT_SUCCESS;
close:
	close(srv_sock);
error_free:
	free(addrstr);
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
