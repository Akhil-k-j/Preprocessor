#include"header.h"
extern char **s;
extern int lc;
extern int cc;
extern int *a;
void comment_replace(char *argv)
{
    FILE*fp=fopen(argv,"r");
    if(fp==0)
    {
        printf("Failed to open the file\n");
        return ;
    }
    char ch;
    int c=0,i=0;
    cc=0;
    lc=0;
    while((ch=fgetc(fp))!=EOF)
    {
        c++;
        if(ch=='\n')
        {
            lc++;
            if(c>cc)
            {
                cc=c;
                c=0;
            }
        }
    }
    cc=cc+1;
    s=calloc(lc,sizeof(char*));
    for(i=0;i<lc;i++)
    s[i]=calloc(cc,sizeof(char));
    rewind(fp);
    for(i=0;i<lc;i++)
    fgets(s[i],cc,fp);     //copying the actual data.
    fclose(fp);
    char *sl="//";
    char *ml1="/*";
    char *ml2="*/";
    char *p1=0,*p2=0,*p=0;
    for(i=0;i<lc;i++)
    {
        if(p=strstr(s[i],sl))
        {
            int j=0;
            while(p[j]!='\n')
            {
                p[j]=' ';
                j++;
            }
        }
    }
    int flag1=0,flag2=0,c1=0,c2=0,line1=0,line2=0;
L1:
    flag1=0,flag2=0,c1=0,c2=0,line1=0,line2=0;
    for(i=0;i<lc;i++)
    {
        if(p1=strstr(s[i],ml1))
        {
            flag1=1;line1=i;break;
        }
    }
    for(;i<lc;i++)
    {
        if(p2=strstr(s[i],ml2))
        {
            flag2=1;line2=i;break;
        }
    } 
    if(flag1==1 && flag2==0)
    {
        printf("ERROR::Unterminated comment(s) -> '*\'  \n");
        exit (0);
    }
    else if(flag1==1 && flag2==1)
    {
        int k=0;
            for(i=line1;i<=line2;i++,k=0)
            {  
                if(i==line1)
                {   
                while(p1[k]!='\n')
                {
                    p1[k]=' ';
                    k++;
                }
                }
                if(i>line1 && i<line2)
                {
                    while(s[i][k]!='\n')
                    {
                        s[i][k]=' ';
                        k++;
                    }
                }
                if(i==line2)
                {   
                while(&s[i][k]<=p2)
                {
                    s[i][k]=' ';
                    k++;
                }
                s[i][k]=' ';
                }
            }
    }
    for(i=0;i<lc;i++)
    if(p1=strstr(s[i],ml1))
    goto L1;
}