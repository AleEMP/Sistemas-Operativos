#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 0x1111

struct sembuf v = {0, +5, SEM_UNDO};

int main() {
	int id = semget(KEY, 1, 0666);
	semop(id, &v, 1);
	return 0;
}
