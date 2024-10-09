#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 0x1111

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

void main()
	{
		int id = semget(KEY, 1, 0666 | IPC_CREAT);
		union semun u;
		u.val=0;
		semctl(id, 0, SETVAL, u);
		semop(id,&p,1);
		for(int i=0;i<1000;i++)
			printf("owo\n");
		sleep(5);
		semop(id,&v,1);
	}