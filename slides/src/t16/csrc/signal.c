#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>

void sigint_hdl(int sig)
{
	static int cnt = 0;
	if (cnt < 2) {
		printf("No quiero morir!!\n");
		cnt++;
	} else{
		printf("Vaaaleee, me muero\n");
		exit(EXIT_SUCCESS);
	}
}

int main()
{
	struct sigaction sa;
	sa.sa_handler = sigint_hdl;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	while(1); // No quiero morir
	return EXIT_SUCCESS;
}
