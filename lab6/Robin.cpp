#include <stdio.h>
#define N 5         
#define T_SLICE 4   
#define NQ 20       

typedef struct{
    int BurtT;
    int ArrivalT;
    int Priority;
}Process;

typedef struct{
    int indexP;
    int BurtT;
}Queue;

typedef struct{
    int indexP;
    int startP;
}Gantt_C;

//Process  burt time , Arrival time , Priority
Process P[N+1]  =  {{0},
        /*P1*/ {    9     ,       1      ,      3},     // P1 = P[1]
        /*P2*/ {    3     ,       1      ,      5},     // P2 = P[2]
        /*P3*/ {    5     ,       3      ,      1},     // P3 = P[3]
        /*P4*/ {    4     ,       4      ,      4},     // P4 = P[4]
        /*P5*/ {    2     ,       7      ,      2}};    // P5 = P[5]


Gantt_C Gantt[20];
Queue   Q[NQ];   
int F = 0, R = 0;
int NG = 0;      
int NT = 0;      
int NP = N;      

void pushQ(int index, int BTimeLeft){
    if (R == F-1  || (F == 1 && R == NQ-1)) {
        printf("OVER FLOW!!\n");
    }else{
        if(R == NQ-1){
            R = 1;
        }else{
            R++;
            if(F == 0)
                F = 1;
        }
        Q[R].indexP = index;               
        Q[R].BurtT  = BTimeLeft;           
    }
}
Queue popQ() {
    Queue index;
    if (F == 0) {
        printf("Remove a process from the queue.\n");
    } else {
        index = Q[F];
        if (F == R) {
            F = 0; R = 0;
        } else {
            if (F == NQ-1)
                F = 1;
            else
                F++;
        }
        return index;
    }
}

int func_FCFS(int index){                 
    int temp[20], n = 0;
    for (int i = 1; i <= NP; i++) {
        if(P[index].ArrivalT == P[i].ArrivalT){
            temp[n++] = i;
        }
    }
    for (int j = 0; j < n; j++) {      
        if(temp[j] != index){
            pushQ(temp[j],P[temp[j]].BurtT);
        }
    }
    return index;                     
}

int duplincate(int index){               
    int count = 0;
    for (int i = 1; i <= NP; i++)
        if(P[index].ArrivalT == P[i].ArrivalT)
            count++;
    if (count > 1)                      
        return func_FCFS(index);        
    else                                
        return index;
}

void Round_Robin(){
    int runingP = 0, timeleft, index, END_P = 0;
    for (int i = 0; i <NT ; i++) {                      
        if(i == END_P && runingP != 0){                 
            pushQ(runingP, timeleft);                   
        }
        for (int j = 1; j <= NP; j++) {
            if (i == P[j].ArrivalT) {                   
                index = j;
                if (i >= END_P && (F ==0 && R == 0 )) { 
                    index = duplincate(index);           
                    if(P[index].BurtT <= T_SLICE) {     
                        END_P = i + P[index].BurtT;     
                        runingP = 0;                    
                    }
                    else {                              
                        END_P = i + T_SLICE;            
                        runingP = index;                
                        timeleft = P[index].BurtT - T_SLICE; 
                    }
                    Gantt[NG].indexP = index;
                    Gantt[NG].startP = i;               
                    NG++;
                    break;
                } else{                                 
                    pushQ(index, P[index].BurtT);       
                    duplincate(index);                 
                    break;
                }
            }
        }
        if (i >= END_P && (F != 0 && R != 0)) {         
            Queue indexQ;
            indexQ = popQ();                            

            if (indexQ.BurtT <= T_SLICE) {              
                END_P = i + indexQ.BurtT;
                runingP = 0;
            } else {                                    
                END_P = i + T_SLICE;
                runingP = indexQ.indexP;;
                timeleft = indexQ.BurtT - T_SLICE;
            }
            Gantt[NG].indexP = indexQ.indexP;
            Gantt[NG].startP = i;
            NG++;
        }
    }
}

float waitProcess(int indexP){                                  
    int count = 0;
    float waitT =0, end = 0;
    for (int i = 0; i <NG ; i++) {
        if(Gantt[i].indexP == indexP){
            if(count == 0){                                     
                waitT += (float)Gantt[i].startP - P[indexP].ArrivalT;
                end    = (float)Gantt[i+1].startP;
                count++;
            }else{
                waitT += (float)Gantt[i].startP - end;          
                end    = (float)Gantt[i+1].startP;
            }
        }
    }
    return waitT;
}

void calNT(){
    int sumBurt = 0;
    int minArrival = P[1].ArrivalT;
    for (int i = 1; i <=NP; ++i) {
        if(P[i].ArrivalT < minArrival){
            minArrival = P[i].ArrivalT;
        }
        sumBurt += P[i].BurtT;
    }
    NT = minArrival + sumBurt;
}

int main(){
    calNT();
     printf("# Kaweewat ID:65543206003-7\n");
    printf("# OUTPUT LAB6 CPU Scheduling\n");
    printf("# Round Robin\n");
    printf("Sequence process is :");
    Round_Robin();
    for (int i = 0; i <NG ; i++) {
        printf("P%d", Gantt[i].indexP);
        if(i<NG-1)
            printf("->");
    }
    printf("\n------------------------------------------------------------\n");
    printf("Wait time of process (millisecond)\n");
    for (int i = 1; i <= NP; i++) {
        printf("| P%-10d", i);
    }
    printf("\n");
    float sum=0;
    float avgTime;
    for (int i = 1; i <= NP; i++) {
        printf("| %-11.2f",waitProcess(i));
        sum += waitProcess(i);
    }
    avgTime = sum/NP;
    printf("\nAverage time is %.2f", avgTime);
    printf("\nTurnaround time\n");
    for (int i = 1; i <= NP; i++) {
        printf("|P%d = %-6.2fms ", i, waitProcess(i) + P[i].BurtT);
    }
    printf("\n------------------------------------------------------------\n");
    return 0;
}
