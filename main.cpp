#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INTCHARBUFFERSIZE   1024
#define LOGMAXPLAYERS       3

int main() {
    char seed[INTCHARBUFFERSIZE];
    sprintf(seed, "%ld",time(NULL));

    for(int i = 0; i < 2; i++) {
        char id[3];
        sprintf(id, "%d", i);

        switch(fork()) {
            case 0  :   execl("./tetrisexe/tetris", "tetris", seed, id, NULL);
                        break;

            default :   break;
        }
    }

    for(int i = 0; i < 2; i++) {
        wait(NULL);
    }

    return 0;
}

// cd /mnt/c/Users/aryag/OneDrive/Documents/GitHub/Tetris
// g++ SFMLTest..cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system