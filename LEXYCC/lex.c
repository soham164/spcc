#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
FILE *fp;
char delim[14] = {' ', '\t', '\n', ',', ';', '(', ')', '{', '}', '[', ']', '#', '<', '>'};
char oper[7][10] = {"int", "float", "char", "double", "bool", "void", "extern", "unsigned", "goto",
"static", "class", "struct", "for", "if", "else", "return", "register", "long", "while", "do"};
char predict[2][12] = {"include", "define"};
char header[6][15] = {"stdio.h", "conio.h", "malloc.h", "process.h", "string.h", "ctype.h"};
void skipcomment();
void analyze();
void check(char[]);
int isdelim(char);
int isop(char);
int fop = 0, numflag = 0, f = 0;
char c, ch, sop;
void main()
{
 char fname[12];
 printf("\nEnter filename: ");
 scanf("%s", fname);
 fp = fopen(fname, "r");
 if (fp == NULL)
 {
 printf("\nThe file does not exist.");
 }
 else
 {
 analyze();
 }
 printf("\nEnd of file\n");
}
void analyze()
{
 char token[256];
 int j = 0;
 while (!feof(fp))
 {
 c = getc(fp);
 if (c == '/')
 {
 skipcomment();
 }
 else if (c == ' ' || c == '\t')
 {
 while ((c = getc(fp)) == ' ' || c == '\t')
 ;
 }
 else if (isalpha(c))
 {
 if (numflag == 1)
 {
 token[j] = '\0';
 check(token);
 numflag = 0;
 j = 0;
 f = 0;
 }
 else
 {
 token[j] = c;
 j++;
 }
 if (f == 0)
 f = 1;
 }
 else if (isdigit(c))
 {
 if (isdelim(c))
 {
 if (numflag == 1)
 {
 token[j] = '\0';
 check(token);
 numflag = 0;
 }
 if (f == 1)
 {
 token[j] = '\0';
 numflag = 0;
 check(token);
 }
 j = 0;
 f = 0;
 printf("\nDelimiter \t%c", c);
 }
 }
 else if (isop(c))
 {
 if (numflag == 1)
 {
 token[j] = '\0';
 check(token);
 numflag = 0;
 j = 0;
 f = 0;
 }
 if (f == 1)
 {
 token[j] = '\0';
 j = 0;
 f = 0;
 numflag = 0;
 check(token);
 }
 if (fop == 1)
 {
 fop = 0;
 printf("\nOperator \t%c%c", c, sop);
 }
 else
 {
 printf("\nOperator \t%c", c);
 }
 }
 else if (c == '.')
 {
 token[j] = c;
 j++;
 }
 else
 {
 token[j] = '\0';
 check(token);
 j = 0;
 }
 }
}
int isdelim(char c)
{
 int i;
 for (i = 0; i < 14; i++)
 {
 if (c == delim[i])
 return 1;
 }
 return 0;
}
int isop(char c)
{
 int i, j;
 char ch;
 for (i = 0; i < 7; i++)
 {
 if (c == oper[i][0])
 {
 ch = getc(fp);
 for (j = 0; j < 6; j++)
 {
 if (ch == oper[j][0])
 {
 fop = 1;
 sop = ch;
 return 1;
 }
 }
 ungetc(ch, fp);
 return 1;
 }
 }
 return 0;
}
void check(char t[])
{
 int i;
 if (numflag == 1)
 {
 printf("\nNumber \t\t%s", t);
 return;
 }
 for (i = 0; i < 2; i++)
 {
 if (strcmp(t, predict[i]) == 0)
 {
 printf("\nPreprocessor directive %s", t);
 return;
 }
 }
 for (i = 0; i < 6; i++)
 {
 if (strcmp(t, header[i]) == 0)
 {
 printf("\nHeader file \t%s", t);
 return;
 }
 }
 for (i = 0; i < 21; i++)
 {
 if (strcmp(t, oper[i]) == 0)
 {
 printf("\nKeyword \t\t%s", t);
 return;
 }
 }
 printf("\nIdentifier \t%s", t);
}
void skipcomment()
{
 ch = getc(fp);
 if (ch == '/')
 {
 while ((ch = getc(fp)) != '\0')
 ;
 }
 else if (ch == '*')
 {
 while (f == 0)
 {
 ch = getc(fp);
 if (ch == '/')
 f = 1;
 }
 }
 f = 0;
}


note:
gcc lex.c -o lex
./lex

Enter fileneame: text.txt
