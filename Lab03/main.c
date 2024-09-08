#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include  <termios.h>
int main() {
   pid_t pid;
   pid = fork();
   int ofd;

   // Child process
   if (pid == 0) {
	system("echo 'hijo'");
       	system("echo $$");
	FILE *file;
       	char linea[256];
	file=fopen("/home/aleemp/SistemasOperativos/Lab03/lec.txt","r");
	if(file==NULL){
		perror("Error al abrir");
	}
	while(fgets(linea,sizeof(linea),file)!=NULL){
		printf("%s",linea);
	}
	fclose(file);
      
   } else {
      system("echo 'padre'");
      system("echo $$");
      sleep(100);
   }
   return 0;
}
