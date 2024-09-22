#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int file;
	int file2;
	pid_t child_pid;
	file=open("write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file2=open("read.txt",O_RDONLY);
	dup2(file,STDOUT_FILENO);
	dup2(file2,STDIN_FILENO);
	child_pid = fork();
	char * list []={"prog.exe",NULL};
       	if (child_pid == 0) {
		char *programa = "./prog.exe";
		char *args[] = { "prog", NULL };
		execv(programa, args);
		perror("Error");
		exit(1);
	}
	else{
		wait(NULL);
	}
	close(file);
   	 close(file2);
}
