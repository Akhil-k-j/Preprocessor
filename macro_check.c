#include"header.h"

///actual file data////
extern char **s;
extern int lc;
extern int cc;
//////////////////////

////macro related data
int mc;             //macro count++ 
char **mreplace2;   //Macro name
char **mreplace1;   //Macro definition
int *m_line;        //Macro line number

int *skip_mline;    //if '#define PI'    only 
int skip_mline_count;  //skippping lines count++
////////////////////////////////

void macro_check(char *argv)
{
    m_line=calloc(lc,sizeof(int));
  
    int i=0;
    char *p;
    char ch;
    mreplace2=calloc(lc,sizeof(char*));
    for(i=0;i<lc;i++)
        mreplace2[i]=calloc(cc+100,sizeof(char));

    mreplace1=calloc(lc,sizeof(char*));
    for(i=0;i<lc;i++)
        mreplace1[i]=calloc(cc+100,sizeof(char));

    skip_mline=calloc(lc,sizeof(int));
    int skip=0;
    for(i=0;i<lc;i++)
    {
        if(p=strstr(s[i],"#define"))
        {
            int j=0;
            while(s[i][j]!='#')        //$hello#define - line only
            {
                if(s[i][j]==' ')
                j++;
                else
                break;
            }
            if(s[i][j]=='#')    //$     #define 
            {
                if((p=strstr(s[i],"#define"))==(&s[i][j]))      //$         #ok#define - neglected, its line
                {
                    if(p[7]==' ')
                    {
                        int c;
                            if((c=count_word(p))>=2)    //#define multiple word conidtion\n        \n characater at last,no space should provide after last letter   
                            {  
                                p=&p[7];
                                while(*p!=' ')
                                {
                                    p++;
                                }
                                p++;            //#define          ->'P'I      3.14
                                int mcc=0;
                                char *m1=p;
                                if(!((*p>='a' && *p<='z') || (*p>='A' && *p<='Z') || (*p=='_' )))
                                {
                                    printf("ERROR:#define $PI use correct naming\n");  //#define &hello
                                exit(0);
                                } 
                                p++;
                                mcc++;
                                while(((*p>='0' && *p<='9') || (*p>='a' && *p<='z') || (*p>='A' && *p<='Z') || *p=='_' ))
                                {
                                        p++;
                                        mcc++;
                                }
                                if(*p==' ' || *p=='\n')   //checking the first word is satisfying the naming rule or not, If not it will go to the else part
                                {
                                     if(c>2)  
                                        {
                                            strncpy(mreplace1[mc],m1,mcc);
                                            p++;
                                            while(*p==' ')
                                            p++;
                                            char *mccc=p;
                                            int count=0;
                                            while(*p!='\n')
                                            {
                                            p++;
                                            count++;
                                            }
                                            strncpy(mreplace2[mc],mccc,count);
                                            m_line[mc]=i;
                                            mc++;                                         
                                        }  
                                        if(c==2)
                                        {
                                            skip_mline[skip++]=i;
                                            skip_mline_count++;
                                            // skip copyine that line.
                                        }   
                                }
                                else
                                {
                                printf("ERROR::#define abc@#$ consider using correct naming conventions\n");  //#define _@k#il
                                exit(0);
                                } 
                            }
                            else
                            {
                                printf("ERROR::#define -> Wrong macro delaration/body is missing\n");  //#define\n        \nright after the last letter.
                                exit(0);
                            }
                    }
                    else
                    {
                    printf("ERROR::#definepi    consider using correct keyword\n");       //$#defineok error
                    exit (0);
                    }
                }
                else
                {
                    printf("ERROR::#errordefine    other characters found before #define\n");   // #ok #define  error
                    exit(0);
                }
            }
        }
    }
}

int count_word(char*p)
{
    int c=0;
    while(*p)
    {
        if(*p==' ')
        {
            while(*p==' ')   //#define        pi           3.14     
            p++;
            c++;
        }
        p++;          //neglecting characters other than ' '
    }
    return c+1;    //considering the last word. (+1)
}

