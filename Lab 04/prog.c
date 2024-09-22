#include <stdio.h>

int main() {
    char linea[100];
    for (int i = 0; i < 10; i++) {
        if (fgets(linea, sizeof(linea), stdin) != NULL) {
            printf("%s", linea);
        } else {
            break; 
        }
    }
    return 0;
}


