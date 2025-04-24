#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct deftab {
char lab[10];
char opc[10];
char oper[10];
} d[10];

int main()
{
char label[10], opcode[10], operand[10];
char macroname[10];
int i, lines;
FILE *f1, *f2, *f3;

f1 = fopen("macin.dat", "r");
if (f1 == NULL) {
printf("Error opening file macin.dat\n");
return 1;
}

f2 = fopen("macout.dat", "w");
if (f2 == NULL) {
printf("Error opening file macout.dat\n");
fclose(f1);
return 1;
}

f3 = fopen("deftab.dat", "w");
if (f3 == NULL) {
printf("Error opening file deftab.dat\n");
fclose(f1);
fclose(f2);
return 1;
}

fscanf(f1, "%s %s %s", label, opcode, operand);

while (strcmp(opcode, "END") != 0) {
if (strcmp(opcode, "MACRO") == 0) {
strcpy(macroname, label);
fscanf(f1, "%s %s %s", label, opcode, operand);
lines = 0;

while (strcmp(opcode, "MEND") != 0) {
fprintf(f3, "%s\t%s\t%s\n", label, opcode, operand);
strcpy(d[lines].lab, label);
strcpy(d[lines].opc, opcode);
strcpy(d[lines].oper, operand);  // Corrected: copy operand, not opcode
fscanf(f1, "%s %s %s", label, opcode, operand);
lines++;
}
}
else if (strcmp(opcode, macroname) == 0) {
printf("Lines=%d\n", lines);
for (i = 0; i < lines; i++) {
fprintf(f2, "%s\t%s\t%s\n", d[i].lab, d[i].opc, d[i].oper);
printf("DLAB=%s\nDOPC=%s\nDOPER=%s\n", d[i].lab, d[i].opc, d[i].oper);
}
}
else {
fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);
}

fscanf(f1, "%s %s %s", label, opcode, operand);
}

fclose(f1);
fclose(f2);
fclose(f3);

printf("FINISHED\n");
return 0;
}