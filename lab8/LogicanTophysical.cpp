#include <stdio.h>
#define NUM_T 5
#define NUM_L 5

typedef struct 
{
	int segment;
	int request;
}Logical;

typedef struct 
{
	int segment;
	int base;
	int length;
}Segmenmt_Table;

Segmenmt_Table Stable[NUM_T]={{0,219,600},
							  {1,2300,14},
							  {2,90,100},
							  {3,1327,580},
							  {4,1952,96}};


Logical logical[NUM_L]={{0,430},
						{1,10},
						{2,500},
						{3,400},
						{4,112}};

void Showtable(){
	printf("Consider the following segment table:\n");
	printf("Segment\t Base\t Length\n");
	for (int i = 0; i < NUM_T; ++i){
		printf("%2d\t%5d\t%5d\n", Stable[i].segment, Stable[i].base, Stable[i].length);
	}
}

int main(){
	int physical;
	Showtable();
	printf("\nWhat are the physical address for the following logical addresses?\n");
	for (int i = 0; i < NUM_L; ++i){
		printf("(%c)segment %2d, request %4d  -> ", 97 + i, logical[i].segment, logical[i].request);
		if(logical[i].request < Stable[i].length){
			physical = Stable[i].base + logical[i].request;
			printf("%4d +%4d = %4d", Stable[i].base, logical[i].request, physical);
		}else{
			printf("Cannot be referenced");
		}
		printf("\n");
	}
	return 0;
}