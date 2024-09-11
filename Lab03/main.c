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
   int fd2[2];
   int fd[2];

   pipe(fd);
   pipe(fd2);

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

        close(fd2[1]);
        FILE * file2;
        file2=fopen("cont.txt","w");
        int num;
        read(fd2[0],&num,sizeof(num));
        fprintf(file2,"%d\n",num);
        fclose(file2);
        close(fd2[0]);
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

        close(fd2[0]);
        write(fd2[1],&i,sizeof(i));
        close(fd2[1]);
        wait(NULL);
   }
   return 0;
}

	
