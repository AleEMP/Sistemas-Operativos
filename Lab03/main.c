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
   pid_t child_pid;
   int fd[2];
   if (pipe(fd) == -1) {
       perror("pipe");
       return 1;
   }
   child_pid = fork();

   // Child process
   if (child_pid == 0) {
        system("echo 'hijo'");
        system("echo $$");
        FILE *file;
        char linea[256];
        file=fopen("lec.txt","r");
        if(file==NULL){
                perror("Error al abrir");
        }
        close(fd[0]);
        while(fgets(linea,sizeof(linea),file)!=NULL){
                write(fd[1],linea,strlen(linea));
        }
        //
        close(fd[1]);
        fclose(file);

   } else {
      system("echo 'padre'");
      system("echo $$");

      char cont[256];
      char*linea;
      close(fd[1]);
      FILE *file;
      file=fopen("esc.txt","w");
      if (file == NULL) {
            perror("fopen");
      }
      int i=0;
      ssize_t n;
      while ((n = read(fd[0], cont, sizeof(cont) - 1)) > 0) {
          cont[n] = '\0';
          linea=strtok(cont,"\n");
          while (linea != NULL) {
              fprintf(file, "%d: %s\n",++i,linea);
              linea = strtok(NULL, "\n");
          }
      }
        fclose(file);
        close(fd[0]);
        wait(NULL);
   }
   return 0;
}

	
