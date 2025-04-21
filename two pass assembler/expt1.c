#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *code[9][4] = {
        {"PRG1", "START", "", ""},
        {"", "USING", "*", "15"},
        {"", "L", "", ""},
        {"", "A", "", ""},
        {"", "ST", "", ""},
        {"FOUR", "DC", "F", ""},
        {"FIVE", "DC", "F", ""},
        {"TEMP", "DS", "1F", ""},
        {"", "END", "", ""}
    };

    char av[3] = {'\0'}; // for register value from USING
    char avail[16]; // availability array from R0-R15
    int i, j, k;
    int count[3], lc[9], loc = 0;

    for (i = 0; i < 16; i++) {
        avail[i] = 'N';
    }

    printf("----------------------------------------------------\n");
    printf("LABEL\t\tOPCODE\n");
    printf("----------------------------------------------------\n\n");

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 4; j++) {
            printf("%s\t\t", code[i][j]);
        }
        printf("\n");
    }

    printf("-----------------------------------------------------\n");
    printf("\nVALUES FOR LC : \n\n");

    for (j = 0; j < 9; j++) {
        if ((strcmp(code[j][1], "START") != 0) &&
            (strcmp(code[j][1], "USING") != 0) &&
            (strcmp(code[j][1], "L") != 0))
            lc[j] = lc[j - 1] + 4;
        else if (strcmp(code[j][1], "START") == 0)
            lc[j] = 0;
        else
            lc[j] = lc[j - 1];

        printf("%d\t", lc[j]);
    }

    printf("\n\nSYMBOL TABLE:\n----------------------------------------------------\n");
    printf("SYMBOL\t\tVALUE\t\tLENGTH\t\tR/A");
    printf("\n----------------------------------------------------\n");

    loc = 0;
    for (i = 0; i < 9; i++) {
        if (strcmp(code[i][1], "START") == 0) {
            printf("%s\t\t%d\t\t%d\t\t%c\n", code[i][0], loc, 4, 'R');
        } else if (strcmp(code[i][0], "") != 0) {
            printf("%s\t\t%d\t\t%d\t\t%c\n", code[i][0], loc, 4, 'R');
            loc += 4;
        } else if (strcmp(code[i][1], "USING") == 0) {
            continue;
        } else {
            loc += 4;
        }
    }

    printf("----------------------------------------------------\n");

    printf("\n\nBASE TABLE:\n-------------------------------------------------------\n");
    printf("REG NO\t\tAVAILABILITY\tCONTENTS OF BASE TABLE");
    printf("\n-------------------------------------------------------\n");

    // Extract register number from USING instruction
    for (j = 0; j < 9; j++) {
        if (strcmp(code[j][1], "USING") == 0) {
            strcpy(av, code[j][3]);
            break;
        }
    }

    // Convert string to integer
    int reg_num = atoi(av);
    if (reg_num >= 0 && reg_num <= 15) {
        avail[reg_num] = 'Y';
    }

    for (k = 0; k < 16; k++) {
        printf(" %d\t\t %c\n", k, avail[k]);
    }

    printf("-------------------------------------------------------\n");

    printf("\nPASS2 TABLE:\n\n");
    printf("LABEL\t\tOP1\t\tLC\n");
    printf("----------------------------------------------------\n");

    for (i = 0; i < 9; i++) {
        printf("%s\t\t%s\t\t%d\n", code[i][0], code[i][1], lc[i]);
    }

    printf("-----------------------------------------------------\n");

    return 0;
}
