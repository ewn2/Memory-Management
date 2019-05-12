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

//Contains the information about the processes in the system, and how they are accessing memory.
struct proc {
    int pid, page; //pid is a numeric value corresponding to a process running on the system
    char action;
    /*
    The action field is interpreted variously:
    - 'C' means the process is created ('page' field not present) => page = -1
    - 'T' means the process terminated ('page' field not present)
    - 'A' means the process allocated memory at address 'page'
    - 'R' means the process read 'page'
    - 'W' means the process wrote to 'page'
    - 'F' means the process freed memory at address 'page
    */
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
        printf("\nUnable to read memory.dat file\n");
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


    int j = 0, physFIFO[20], physLRU[20], physRAN[20];
    while (j < 20)
    {
        physFIFO[j] = 0;
        j++;
    }
    memcpy(physLRU, physFIFO, 20);
    memcpy(physRAN, physFIFO, 20);
    int virt[50]; //10ˆ15 bytes of virtual address space for process-> 50 bits for virtual address
    /*
    The virtual address that the process generated has 2 components: the virtual page number and the offset within the page.
    Our program should implement a virtual memory system with 20 physical pages.
    */
    j = 0;
    int t = 0, n = 0;
    while (j <= all) {
        if (input[j].action == 'A') {//FIFO will be implemented here
            if (physFIFO[input[j].page] == 0)
            {
                physFIFO[input[j].page] = input[j].pid;
            }
            else {
                while(t <= 20 && n == 0) {
                    if (physFIFO[t] == 0) {
                        physFIFO[t] = input[j].pid;
                        n = 1;
                    }
                    t++;
                }
                t = 0;
                n = 0;
            }
        }
        if (input[j].action == 'R' || input[j].action == 'W' || input[j].action == 'F') {
            if(physFIFO[input[j].page] = input[j].pid) {
                if (input[j].action == 'F') {
                    physFIFO[input[j].page] = 0;
                }
            }
            else {
                int r = 0;
                while (r < 20) {
                    if (physFIFO[r] == input[j].pid) {
                        physFIFO[r] = 0;
                    }
                    r++;
                }
            }
        }
        if (input[j].action == 'T') {
            int r = 0;
            while (r < 20) {
                if (physFIFO[r] == input[j].pid) {
                    physFIFO[r] = 0;
                }
                r++;
            }
        }
        j++;
    }




    printf("\nFIFO Policy\n");
    j = 0;
    while (j < 20) {//Added to check stored memory.dat values
        printf("\nMemory Location %i: %i", j, physFIFO[j]);
        j++;
    }
    j = 0;
    int p = 0;
    printf("\n");
    while (j < all) {//Must adjust later so it does not repeat unecessarily
        printf("\nProcess %i exists in Location(s): ", input[j].pid);
        while (p < 20) {
            if (physFIFO[p] == input[j].pid){
                printf("%i ", p);
            }
            p++;
        }
        p = 0;
        j++;
    }
    fclose(memList);
}
