#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define MAXSIZE     128

void die(char *s) {
    perror(s);
    exit(1);
}

struct msgbuf {
    long mtype;
    int stype;
    int pid;
};

int main() {
    int msqid;
    key_t key = 1234;
    struct msgbuf rcvbuffer;

    // Crea la cola de mensajes
    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid < 0) {
        die("msgget()");
    }

    int pid = fork();
    if (pid < 0) {
        die("fork failed");
    }

    if (pid == 0) {
        while (1) {
            // Recibe un mensaje de tipo 1
            if (msgrcv(msqid, &rcvbuffer, sizeof(rcvbuffer) - sizeof(long), 1, 0) < 0) {
                die("msgrcv");
            }
            printf("Mensaje recibido: PID = %d, Data = %d\n", rcvbuffer.pid, rcvbuffer.stype);
            kill(rcvbuffer.pid, rcvbuffer.stype);
        }
    } else {
        while (1) {
            // Recibe un mensaje de tipo 2
            if (msgrcv(msqid, &rcvbuffer, sizeof(rcvbuffer) - sizeof(long), 2, 0) < 0) {
                die("msgrcv");
            }
            printf("Mensaje recibido: PID = %d, Data = %d\n", rcvbuffer.pid, rcvbuffer.stype);
            kill(rcvbuffer.pid, rcvbuffer.stype);
        }
    }
    return 0;
}

