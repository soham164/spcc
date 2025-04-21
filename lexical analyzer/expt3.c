#include<stdio.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
#include<process.h>
#include<ctype.h>

FILE *fp;
char delim[14]={' ','\t','\n',',',';','(',')','{','}','[',']','#','<','>'};
char key[21][15]={"int","float","char","double","bool","void","extern","unsigned","goto","static","class","struct","for","if","else","return","register","long","while","do","switch"};
char predirect[2][12]={"include","define"};
char header[6][15]={"stdio.h","conio.h","malloc.h","process.h","string.h","ctype.h"};

void skipcomment();
void analyze();
void check(char[]);
int isdelim(char);
int isop(char);

int fop=0, numflag=0, f=0;
char c, ch, sop;

void main()
{
    char fname[12];
    printf("\n Enter filename: ");
    scanf("%s", fname);
    fp=fopen(fname, "r");
    if(fp==NULL)
        printf("\nThe file does not exist");
    else
        analyze();
    printf("\n End of file \n");
    getchar();
}

void analyze()
{
    char token[50];
    int j=0;
    
    while(!feof(fp))
    {
        c=getc(fp);
        if(c=='/')
        {
            skipcomment();
        }
        else if(c==' ' || c=='\t' || c=='\n')
        {
            if(numflag==1)
            {
                token[j]='\0';
                check(token);
                numflag=0;
                j=0;
                f=0;
            }
            else if(f==1)
            {
                token[j]='\0';
                check(token);
                j=0;
                f=0;
            }
        }
        else if(isalpha(c))
        {
            token[j]=c;
            j++;
            if(f==0)
                f=1;
        }
        else if(isdigit(c))
        {
            token[j]=c;
            j++;
            numflag=1;
        }
        else
        {
            if(isdelim(c))
            {
                if(numflag==1)
                {
                    token[j]='\0';
                    check(token);
                    numflag=0;
                }
                if(f==1)
                {
                    token[j]='\0';
                    check(token);
                }
                j=0;
                f=0;
                printf("\n Delimiter \t%c", c);
            }
            else if(isop(c))
            {
                if(numflag==1)
                {
                    token[j]='\0';
                    check(token);
                    numflag=0;
                    j=0;
                    f=0;
                }
                if(f==1)
                {
                    token[j]='\0';
                    j=0;
                    f=0;
                    numflag=0;
                    check(token);
                }
                if(fop==1)
                {
                    fop=0;
                    printf("\n Operator \t%c%c", c, sop);
                }
                else
                    printf("\n Operator \t%c", c);
            }
            else if(c=='.')
            {
                token[j]=c;
                j++;
            }
        }
    }
}

int isdelim(char c)
{
    int i;
    for(i=0; i<14; i++)
    {
        if(c==delim[i])
            return 1;
    }
    return 0;
}

int isop(char c)
{
    int i;
    char ch;
    char oper[7]={'+','-','*','/','%','=','!'};
    
    for(i=0; i<7; i++)
    {
        if(c==oper[i])
        {
            ch=getc(fp);
            if(ch=='=' || (c=='+' && ch=='+') || (c=='-' && ch=='-'))
            {
                fop=1;
                sop=ch;
                return 1;
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
    if(numflag==1)
    {
        printf("\n Number \t\t%s", t);
        return;
    }
    
    for(i=0; i<2; i++)
    {
        if(strcmp(t, predirect[i])==0)
        {
            printf("\n Preprocessor directive %s", t);
            return;
        }
    }
    
    for(i=0; i<6; i++)
    {
        if(strcmp(t, header[i])==0)
        {
            printf("\n Header file \t%s", t);
            return;
        }
    }
    
    for(i=0; i<21; i++)
    {
        if(strcmp(key[i], t)==0)
        {
            printf("\n Keyword \t\t%s", key[i]);
            return;
        }
    }
    
    printf("\n Identifier \t%s", t);
}

void skipcomment()
{
    ch=getc(fp);
    if(ch=='/')
    {
        while((ch=getc(fp))!='\n' && ch!=EOF);
    }
    else if(ch=='*')
    {
        f=0;
        while(f==0 && ch!=EOF)
        { 
            ch=getc(fp);
            if(ch=='*')
            {
                ch=getc(fp);
                if(ch=='/')
                    f=1;
            }
        }
    }
    else
    {
        ungetc(ch, fp);
    }
}