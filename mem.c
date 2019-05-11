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
    struct proc input[200];
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
        if (input[i].action == 'C' || input[i].action == 'T') {
            input[i].page = -1;
        }
        all++;
        i++;
    }
    all--;
    all--;
    int j = 0;
    printf("\n");
    j = 0;
    int phys[30];
    while (j < 30)
    {
        phys[j] = 0;
        j++;
    }
    int virt[50];
    j = 0;
    int t = 0;
    while (j <= all) {
        if (input[j].action == 'A') {
            if (phys[input[j].page] == 0)
            {
                phys[input[j].page] = input[j].pid;
            }
            else {
                while(t <= 30)
                {
                    if (phys[input[j].page] == 0) {
                        phys[t] = input[j].pid;
                    }
                    t++;
                }
                t = 0;
            }
        }
        if (input[j].action == 'R' || input[j].action == 'W' || input[j].action == 'F') {
            if(phys[input[j].page] = input[j].pid) {
                if (input[j].action == 'F') {
                    phys[input[j].page] = 0;
                }
            }
            else {
                int r = 0;
                while (r < 20) {
                    if (phys[r] == input[j].pid) {
                        phys[r] = 0;
                    }
                    r++;
                }
            }
        }
        if (input[j].action == 'T') {
            int r = 0;
            while (r < 20) {
                if (phys[r] == input[j].pid) {
                    phys[r] = 0;
                }
                r++;
            }
        }
        j++;
    }
    j = 0;
    while (j < 30) {//Added to check stored memory.dat values
        printf("\nLocation %i: %i", j, phys[j]);
        j++;
    }
    printf("\n");
    fclose(memList);
}