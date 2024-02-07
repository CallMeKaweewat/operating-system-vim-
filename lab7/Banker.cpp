#include <stdio.h>

int np,nr;     
int Allocation[10][5],Max[10][5],Need[10][5],Available[10][5];  
int resource[5],state[10],AvailDrives[5],AvailSUM[5];  
int returnResources = 1;

void calAvailable(){ 
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < np; ++j) {
            AvailDrives[i] += Allocation[j][i];
        }
        AvailDrives[i] = resource[i] - AvailDrives[i];
        AvailSUM[i] = AvailDrives[i];
    }
}
void calNeed(){  
    for (int i = 0; i < np; ++i) { 
        for (int j = 0; j < nr; ++j) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}
void availSum(int i){  
    for (int j = 0; j < nr; ++j) {
        Available[i][j] = Allocation[i][j] + AvailSUM[j];
        AvailSUM[j] = Available[i][j];
    }
}
void Banker(){
    int Level = 0;
    for (int round = 1;returnResources == 1; ++round) {
        returnResources = 0; 
        for (int i = 0; i < np; ++i) {          
            if(round == 1 || (round  >1 && state[i] == -1)) {
                
                for (int j = 0; j < nr; ++j) {  
                    Available[i][j] =-1;        
                    if (AvailSUM[j] >= Need[i][j]) {  
                        if (j == nr - 1) {      
                            availSum(i);        
                            state[i] = Level+=1; 
                            returnResources = 1; 
                        }
                    } else {                     
                        state[i] = -1;            
                        Available[i][j] =-1;      
                        break;
                    }
                }
            }
        }
    }
}

void input(){
    printf("->> Input state\n");
    printf("Enter number of process :");
    scanf("%d", &np);
    printf("Enter number of resource (instances) :");
    scanf("%d", &nr);
    printf("------------------------------------------------------\n");
    printf("Enter all unit of resource :\n");
    for (int i = 0; i < nr; ++i) {
        printf(" resource P%d (instances A,B) : ", i + 1);
        scanf("%d", &resource[i]);
    }
    printf("\n------------------------------------------------------");
    //allo
    

    for (int i = 0; i < np; ++i) {
        printf("\nallocation process : %d\n", i + 1);
        for (int j = 0; j < nr; ++j) {
            printf("allocation %c : ", 'a' + j); 
            scanf("%d", &Allocation[i][j]);
        }
    }

    
    for (int i = 0; i < np; ++i) {
        printf("\nAllocation process %d:\n", i + 1);
        for (int j = 0; j < nr; ++j) {
            printf("allocation %c : %d\n", 'a' + j, Allocation[i][j]);
        }
    }
    //

    // MAX
    printf("------------------------------------------------------\n");
    

    for (int i = 0; i < np; ++i) {
        printf("\nEnter max of process : %d\n", i + 1);
        for (int j = 0; j < nr; ++j) {
            printf("Max %c : ", 'a' + j); 
            scanf("%d", &Max[i][j]);
        }
    }

    
    for (int i = 0; i < np; ++i) {
        printf("\nMax for process %d:\n", i + 1);
        for (int j = 0; j < nr; ++j) {
            printf("Max %c : %d\n", 'a' + j, Max[i][j]);
        }
    }
    //
    printf("------------------------------------------------------\n");
}
    
void inTable(int i, int temp[][5]) {
    for (int j = 0; j < nr; ++j) {
        if(temp[i][j] == -1) {
            printf("        ");
            break;
        }
        else
            printf("%2d ", temp[i][j]);
    }
}
void showTable(){ 
    printf("\n================================================================\n");
    printf("Poscess      Allocation      Max      Need       Avail      State\n         ");
    for (int i = 0; i < 4; ++i){
        printf("  ");
        for (int j = 0; j < nr; ++j)
            printf("%c  ", 65 + j);
    }
    printf("\n");
    for (int i = 0; i < np; ++i){
        printf("P%d\t  ",i+1);
        inTable(i,Allocation);printf("  ");
        inTable(i, Max);printf("  ");
        inTable(i, Need);printf("  ");
        inTable(i, Available);printf("    ");
        if(state[i] == -1)
            printf("NULL");
        else
            printf("%d", state[i]);
        printf("\n");
    }
    printf("===========================================================\n");
}
void Process(){
    printf("Available drives = ");
    for (int i = 0; i < nr; ++i)
        printf("%d ", AvailDrives[i]);

    int First = 0;               
    for (int i = 0; i < np; ++i)  
        if(state[i] == 1) {
            First = i + 1;
            break;
        }
    if(First !=0){        
        printf("\nFirst state allocate(");
        for (int i = 0; i < nr; ++i)
            printf("%d,", Need[First-1][i]);
        printf(") drives to ");
        printf("P%d\n", First);
        printf("P%d completes and releases(", First);
        for(int i = 0; i<nr; i++)
            printf("%d,",Available[First-1][i]);
        printf(")Available drives\n");
        printf("Next state ...\n");
    }

    int countNULL = 0;
    for (int i = 0; i < np; ++i)
        if(state[i] == -1)  
            countNULL +=1;  

    if(countNULL == np)    
        printf("\nIf grant last drive to any process may get deadlock = UNSAFE STATE\n**ALL process don't run to completion\n");
    else if(countNULL > 0 && countNULL < np) {  
        printf("Not enough for process needs remaining(");
        for (int i = 0; i < np; ++i)
            if(state[i] == -1)
                printf("P%d,",i+1);
        printf(")\nProcess may get deadlock = UNSAFE STATE\n");
    }
    else {    
        printf("Sequences state are ");
        for (int i = 1; i <=np ; ++i)
            for (int j = 0; j <np ; ++j)
                if(i == state[j])
                    printf("P%d ",j+1);
        printf("\n**ALL process run to completion = SAFE STATE\n");
        printf("===========================================================\n");
    }

}

int main(){
    input();   
    calAvailable();
    calNeed();
    Banker();  

    printf("%d process\n", np);
    printf("%d resource is ", nr);
    for (int i = 0; i < nr; ++i)
        printf("%c(%d instances) ", 65 + i, resource[i]);

    showTable();  
    Process();     
}
