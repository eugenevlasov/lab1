#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
pid_t pid;
FILE *mf;

char filename[20];

switch(pid=fork())
{
case -1: /*Ошибка*/
	perror("fork");
	exit(1);

case 0: /*Дочерний процесс*/                                        sleep(1);
	printf("\nCHILD: Это дочерний процесс\n");                sleep(1);
	printf("CHILD: PID: %d\n", getpid());                       sleep(1);
	printf("CHILD: PPID: %d\n", getppid());                   sleep(1);

	sprintf(filename,"file_%d.txt", getpid());
	mf=fopen(filename, "w");
	fprintf(mf, "%d", getppid());
	fclose(mf);

	printf("CHILD: Файл создан\n");

	exit(0);

default: /*Родительский процесс*/
	wait(0);
	printf("\nPARENT: Это Родительский процесс\n");           sleep(1);
	printf("PARENT: PID: %d\n", getpid());                      sleep(1);
	printf("PARENT: PID потомка: %d\n", pid);                   sleep(1);

        sprintf(filename,"file_%d.txt", getpid());
	mf=fopen(filename, "w");
	fprintf(mf, "%d\n%d", getpid(), pid);
	fclose(mf);

	printf("PARENT: Файл создан\n");

	/*printf("PARENT: Ожидание завершения процесса-потомка\n");   sleep(1);*/

	printf("PARENT: Выход!\n\n");                               sleep(1);
	exit(0);
}
}
