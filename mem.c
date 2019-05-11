#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

struct proc {
    int pid;
    char action;
    int page;
};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    char line[200];
    int i = 0, all = 1, current;
    FILE *memList;
    struct proc input[100];
    time_t theTime;
    struct tm * timeinfo;
    time (&theTime);
    timeinfo = localtime(&theTime);
    time_t start = theTime;
    memList = fopen ("memory.dat", "r");
    if (memList == NULL) {
        printf("\nUnable to either read memory.dat file\n");
        exit (1);
    }
    while(fgets(line, sizeof(line), memList) != NULL && i < all) {
        current = sscanf(line, "%i %c %i", &input[i].pid, &input[i].action, &input[i].page);
        if (input[i].action == 'C' || input[i].action == 'T')
        {
            input[i].page = -1;
        }
        all++;
        i++;
    }
    all--;
    all--;
    int j = 0;
    while (j <= all) {//Added to check stored memory.dat values
        printf("\n%i %c %i", input[j].pid, input[j].action, input[j].page);
        printf("---%i", j);
        j++;
    }
    printf("\n");
    
    fclose(memList);
}