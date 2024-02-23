#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define NUM_PROCESSES 6
#define NUM_LOGICAL_ADDRESSES 4

typedef struct {
    int page_number;
    char offset[100];
} LogicalAddress;

typedef struct {
    int page_number;
    char offset[100];
} ProcessPage;

char output_str[100] = "";
int memory_pages = 8;
int system_bus = 24;
ProcessPage PageTable[NUM_PROCESSES + 1] = {{},
                                            {1, "0000010100101001"},
                                            {2, "0000010100100011"},
                                            {3, "0000000100100100"},
                                            {4, "0000110101101011"},
                                            {5, "0000001101101100"},
                                            {6, "0000111101100111"}};
LogicalAddress logical_addresses[NUM_LOGICAL_ADDRESSES + 1] = {{},
                                                               {1, "25"},
                                                               {2, "43"},
                                                               {3, "7A"},
                                                               {5, "50"}};

void binaryToHex(char *output, char binary[]) {
    int dec = 0;
    char numchar;

    for (int i = 0; i < strlen(binary); i += 4) {
        for (int j = 0; j <= 3; j++) {
            dec += (binary[i + j] - '0') * (int)pow(2, 3 - j);
        }
        switch (dec) {
            case 15:
                strcat(output, "F");
                break;
            case 14:
                strcat(output, "E");
                break;
            case 13:
                strcat(output, "D");
                break;
            case 12:
                strcat(output, "C");
                break;
            case 11:
                strcat(output, "B");
                break;
            case 10:
                strcat(output, "A");
                break;
            default:
                numchar = dec + '0';
                strncat(output, &numchar, 1);
        }
        dec = 0;
    }
}

void hexToBinary(char *output, char hex[]) {
    for (int i = 0; i < strlen(hex); ++i) {
        switch (hex[i]) {
            case '0':
                strcat(output, "0000");
                break;
            case '1':
                strcat(output, "0001");
                break;
            case '2':
                strcat(output, "0010");
                break;
            case '3':
                strcat(output, "0011");
                break;
            case '4':
                strcat(output, "0100");
                break;
            case '5':
                strcat(output, "0101");
                break;
            case '6':
                strcat(output, "0110");
                break;
            case '7':
                strcat(output, "0111");
                break;
            case '8':
                strcat(output, "1000");
                break;
            case '9':
                strcat(output, "1001");
                break;
            case 'A':
                strcat(output, "1010");
                break;
            case 'B':
                strcat(output, "1011");
                break;
            case 'C':
                strcat(output, "1100");
                break;
            case 'D':
                strcat(output, "1101");
                break;
            case 'E':
                strcat(output, "1110");
                break;
            case 'F':
                strcat(output, "1111");
                break;
        }
    }
}

char *convertBase(char *output, char number[], char base[]) {
    strcpy(output_str, "");
    if (strcmp(base, "2") == 0) {
        hexToBinary(output_str, number);
    } else if (strcmp(base, "16") == 0) {
        binaryToHex(output_str, number);
    } else {
        return "error";
    }
    return output_str;
}

void display() {
    printf("------------------------------------------------------------\n");
    printf("Memory per Page (256 Byte) = (2^8) = 8 bit \n");
    printf("CPU Address bus                     = 24 bit \n");
    printf("------------------------------------------------------------\n");
    printf("\n");
    printf("Logical Address to Physical Address Method Paging\n");
    printf("------------------------------------------------------------\n");
    printf("Logical Address\t\t");
    printf("Process Page Table\n");
    for (int i = 1; i < NUM_PROCESSES + 1; ++i) {
        if (logical_addresses[i].page_number != 0)
            printf("%02d %3sH\t\t\t", logical_addresses[i].page_number, logical_addresses[i].offset);
        else
            printf("\t\t\t");
        printf("page: %d  %sB", PageTable[i].page_number, PageTable[i].offset);
        printf("\n");
    }
    printf("------------------------------------------------------------\n");

}

void physicalAddressConversion() {
    for (int i = 1; i < NUM_LOGICAL_ADDRESSES + 1; ++i) {
        for (int j = 1; j < NUM_PROCESSES + 1; ++j) {
            if (logical_addresses[i].page_number == PageTable[j].page_number) {
                printf("Logical\t%sH\t\t%024s B\n", logical_addresses[i].offset, convertBase(output_str, logical_addresses[i].offset, "2"));
                printf("\t%02d\t=\tPage No.%d\n", logical_addresses[i].page_number, logical_addresses[i].page_number);
                printf("\t%2s\t=\tPage off.%s\n", logical_addresses[i].offset, logical_addresses[i].offset);
                
                printf("Physical\t\tf = %s B\n", PageTable[j].offset);
                printf("\n");
                printf("\t\t\t%7sFrame No. | Page off.\n", "");
                printf("Physical Address\t%s | %s B\n", PageTable[j].offset, convertBase(output_str, logical_addresses[i].offset, "2"));
                printf("\t\t\t%11s %s | %s H\n", "", convertBase(output_str, PageTable[j].offset, "16"), logical_addresses[i].offset);
                printf("------------------------------------------------------------\n");
                break;
            }
        }
    }
}

int main() {
    display();
    physicalAddressConversion();
    return 0;
}
