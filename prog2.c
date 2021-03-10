#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 5000000
#define COLS 8192

int main(int argc, char const *argv[]){
    int cnt     = 0,
        **arr   = NULL;

    arr = (int**)malloc(ROWS * sizeof(int *));
    for (int i = 0; i < ROWS; i++)
        arr[i] = (int*)malloc(COLS * sizeof(int));

    for (int c = 0; c < COLS; c++)
        for (int r = 0; r < ROWS; r++)
            arr[r][c] = cnt++;

    free(arr);
            
    return 0;
}
