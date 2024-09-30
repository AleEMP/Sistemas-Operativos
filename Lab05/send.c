#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define MAXSIZE     128

void die(char *s)
{
  perror(s);
  exit(1);
}

struct msgbuf
{
    long mtype;
    int stype;
    int pid;
};

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;

    key = 1234;

    if ((msqid = msgget(key, msgflg)) < 0)   //Get the message queue ID for the given key
      die("msgget");

    //Message Type
    int opcion,pid;
    do {
        printf("\n--- Menú ---\n");
        printf("1. Signal 2 SIGINT\n");
        printf("2. Signal 9 SIGHUP\n");
        printf("3. Signal 18 SIGCONT\n");
	printf("4. Signal 19 SIGSTOP\n");
	printf("5. Salir\n");
        printf("Selecciona una opción:");
        scanf("%d", &opcion);
	printf("%d",opcion);
	if(opcion>=1 && opcion<=4){
		switch(opcion) {
		       	case 1:
				sbuf.stype = 2;
				sbuf.mtype = 1;
			       	break;
			case 2:
			       	sbuf.stype =9;
				sbuf.mtype = 1;
			       	break;
		       	case 3:
				sbuf.stype =18;
				sbuf.mtype = 2;
			       	break;
			case 4:
				sbuf.stype =19;
				sbuf.mtype = 2;
			       	break;
			default:
				printf("Opción no válida, intenta de nuevo.\n");
		}
		 printf("Introduce el PID del proceso: ");
		 scanf("%d", &pid);
		 sbuf.pid = pid;
		 if (msgsnd(msqid, &sbuf, sizeof(sbuf) - sizeof(long), IPC_NOWAIT) == -1) {
			 perror("Error al enviar el mensaje");
			 return 1;
		 }
		 printf("Mensaje enviado: PID = %d, Tipo de senal = %d\n", sbuf.pid, sbuf.stype);
	}
    } while(opcion != 5);
}
