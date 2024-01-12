#include <stdio.h>
#define NP 5

typedef struct {
    int indexP;
    int startP;
} GanttChart;

typedef struct {
    int indexP;
    int BurtT;
} Queue;

typedef struct {
    int BurtT;
    int ArrivalT;
    int Priority;
} Process;

Process P[NP + 1] = {{0},
                     /*P1*/ {9, 1, 3},
                     /*P2*/ {3, 1, 5},
                     /*P3*/ {5, 3, 1},
                     /*P4*/ {4, 4, 4},
                     /*P5*/ {2, 7, 2}};

GanttChart Gantt[30];
Queue Q[30];
int NT = 0;  // Time
int NG = 0;  // Number GanttChart
int SP = 0;  // Pointer in Queue

void push(int indexP) {
    SP++;
    Q[SP].indexP = indexP;
    Q[SP].BurtT = P[indexP].BurtT;
}

void pop() {
    if (SP == 0)
        printf("Remove a process from the queue.\n");
    SP--;
}

Queue sortQ() {
    Queue tempP;
    int j;
    for (int i = 1; i < SP; ++i) {
        j = i + 1;
        if (Q[i].BurtT <= Q[j].BurtT) {
            tempP = Q[i];
            Q[i] = Q[j];
            Q[j] = tempP;
        }
    }
    return Q[SP];
}

int minBurt(int indexP, int tempP[], int *countP) {
    int minBurt = P[indexP].BurtT;
    int minPro = indexP;
    *countP = 0;
    for (int i = 1; i <= NP; ++i)
        if (P[indexP].ArrivalT == P[i].ArrivalT) {
            tempP[*countP] = i;
            *countP += 1;
            if (P[i].BurtT < minBurt) {
                minBurt = P[i].BurtT;
                minPro = i;
            }
        }
    return minPro;
}

void pushSynchronous(int indexP, int tempP[], int countP) {
    for (int i = 0; i < countP; ++i)
        if (tempP[i] != indexP)
            push(tempP[i]);
}

void getData(int indexP, int time_i) {
    Gantt[NG].indexP = indexP;
    Gantt[NG].startP = time_i;
    NG++;
}

void SJF_NP() { //
    int indexP = 0, ENDPro = 0;
    int tempP[NP], countP = 0;
    for (int i = 0; i <= NT; ++i) {
        for (int j = 1; j <= NP; ++j) {
            if (i == P[j].ArrivalT) {
                indexP = minBurt(j, tempP, &countP);
                if (i >= ENDPro && SP == 0) {
                    pushSynchronous(indexP, tempP, countP);
                    ENDPro = i + P[indexP].BurtT;
                    getData(indexP, i);
                } else {
                    push(indexP);
                    pushSynchronous(indexP, tempP, countP);
                }
                break;
            }
        }
        if (i >= ENDPro && SP != 0) {
            Queue indexPQ;
            indexPQ = sortQ();
            pop();
            ENDPro = i + indexPQ.BurtT;
            getData(indexPQ.indexP, i);
        }
    }
}

float waitProcess(int indexP) {
    int count = 0;
    float waitT = 0, end = 0;
    for (int i = 0; i < NG; i++) {
        if (Gantt[i].indexP == indexP) {
            if (count == 0) {
                waitT += (float)Gantt[i].startP - P[indexP].ArrivalT;
                end = (float)Gantt[i + 1].startP;
                count++;
            } else {
                waitT += (float)Gantt[i].startP - end;
                end = (float)Gantt[i + 1].startP;
            }
        }
    }
    return waitT;
}

void calNT() {
    int sumBurt = 0;
    int minArrival = P[1].ArrivalT;
    for (int i = 1; i <= NP; ++i) {
        if (P[i].ArrivalT < minArrival) {
            minArrival = P[i].ArrivalT;
        }
        sumBurt += P[i].BurtT;
    }
    NT = minArrival + sumBurt;
}

int main() {
    calNT();
    printf("# Kaweewat Kansupattanakuk ID:65543206003-7\n");
    printf("# OUTPUT LAB6 CPU Scheduling\n");
    printf("# SJF Non Preemptive \n");
    printf("Sequence process is :");
    SJF_NP();
    for (int i = 0; i < NG; i++) {
        printf("P%d", Gantt[i].indexP);
        if (i < NG - 1)
            printf("->");
    }
    printf("\n------------------------------------------------------------\n");
    printf("Wait time of process (millisecond)\n");
    for (int i = 1; i <= NP; i++) {
        printf("| P%-10d", i);
    }
    printf("\n");
    float sum = 0, avgTime;
    for (int i = 1; i <= NP; i++) {
        printf("| %-11.2f", waitProcess(i));
        sum += waitProcess(i);
    }
    avgTime = sum / NP;
    printf("\nAverage time is %.2f", avgTime);
    printf("\nTurnaround time\n");
    for (int i = 1; i <= NP; i++) {
        printf("|P%d = %-6.2fms ", i, waitProcess(i) + P[i].BurtT);
    }
    printf("\n------------------------------------------------------------\n");
    return 0;
}
