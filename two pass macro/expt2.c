#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct deftab
{
    char lab[10];
    char opc[10];
    char oper[10];
} d[10];

void main()
{
    char label[10], opcode[10], operand[10], macroname[10];
    int i, lines;
    FILE *f1, *f2, *f3;
    
    f1 = fopen("macin.dat", "r");
    f2 = fopen("macout.dat", "w");
    f3 = fopen("deftab.dat", "w");
    
    fscanf(f1, "%s %s %s", label, opcode, operand);
    
    while(strcmp(opcode, "END") != 0)
    {
        if(strcmp(opcode, "MACRO") == 0)
        {
            strcpy(macroname, label);
            fscanf(f1, "%s %s %s", label, opcode, operand);
            lines = 0;
            
            while(strcmp(opcode, "MEND") != 0)
            {
                fprintf(f3, "%s\t%s\t%s\n", label, opcode, operand);
                strcpy(d[lines].lab, label);
                strcpy(d[lines].opc, opcode);
                strcpy(d[lines].oper, operand);  // Fixed: was copying opcode into oper
                fscanf(f1, "%s %s %s", label, opcode, operand);
                lines++;
            }
        }
        else if(strcmp(opcode, macroname) == 0)
        {
            printf("Lines=%d\n", lines);
            for(i = 0; i < lines; i++)
            {
                fprintf(f2, "%s\t%s\t%s\n", d[i].lab, d[i].opc, d[i].oper);
                printf("DLAB=%s\nDOPC=%s\nDOPER=%s\n", d[i].lab, d[i].opc, d[i].oper);
            }
            fscanf(f1, "%s %s %s", label, opcode, operand);  // Added: read next line after expanding macro
        }
        else
        {
            fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);  // Fixed: added operand
            fscanf(f1, "%s %s %s", label, opcode, operand);  // Added: read next line
        }
    }
    
    // Write the END statement to output
    fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);
    
    fclose(f1);
    fclose(f2);
    fclose(f3);
    printf("FINISHED");
    getchar();
}