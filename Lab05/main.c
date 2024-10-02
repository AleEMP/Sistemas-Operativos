#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal_num) {
    printf("Señal %d capturada\n", signal_num);
}

int main() {
    signal(SIGINT, signal_handler);  
    signal(SIGKILL, signal_handler);   
    signal(SIGTERM, signal_handler);
    signal(SIGCONT, signal_handler);
    signal(SIGSTOP, signal_handler);  
    while (1) {
        printf("Esperando señales...\n");
        sleep(2); 
    }
    return 0;
}
