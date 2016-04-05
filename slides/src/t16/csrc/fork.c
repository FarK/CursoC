#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid;
	int var = 0;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		printf("Soy el hijo\n\tPID = %d\n",
		       getpid());

		var = 10;
		printf("var del hijo = %d\n", var);
	} else {
		printf("Soy el padre\n\tPID = %d\n\tPID hijo = %d\n", getpid(), pid);

		wait(NULL); // Esperamos a que termine el hijo
		printf("var del padre = %d\n", var);
	}

	return EXIT_SUCCESS;
}
