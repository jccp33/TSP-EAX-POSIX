
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POINTS 50

int main(int argc, char **argv){
	srand(time(NULL));
    int x, y;

    for(int i=0; i<POINTS; i++){
        x = rand() % 50 + 1;
        y = rand() % 50 + 1;
        printf("%d\t%d\t%d\n", (i+1), x, y);
    }
}
