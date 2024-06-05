#include"header.h"

extern char *filename;
extern int lc;
extern char **s;
extern int cc;
extern char **replace;
extern int *a;
void header_replace(char *argv)
{
    int i=0;
    int offset=0;
    char *p1,*p2;
    int flag1=0,flag2=0;
    int header_flag=0;

    //creating buffer and array to store the line where the Header inclusion take place and also the header file path.
    a=calloc(lc,sizeof(int));
    replace=calloc(lc,sizeof(int*));
   
    for(i=0;i<lc;i++)
    replace[i]=calloc(cc,sizeof(char));

    //checking for header file inclusion.
    for(i=0;i<lc;i++)
    {
        if(p1=strstr(s[i],"#include"))
        {
            int j=0;
            while(s[i][j]!='#')
            {
                if(s[i][j]==' ')
                j++;
                else
                break;
            }
            if(s[i][j]=='#')
            {
                int k=j,l=0;
                if((strstr(s[i],"<")==NULL) && (strstr(s[i],"\"")==NULL))
                {
                printf("ERROR::#include_____->Error\n");
                exit(0);
                }
                if(p1=strstr(s[i],"<"))
                {
                    l=k+8;
                while(s[i][l]!='<')
                {
                    if(s[i][l]==' ')
                    l++;
                    else
                    break;
                }
                if(s[i][l]=='<')
                {
                    int m=l;
                    if(p2=strstr(s[i]+l+1,">"))
                    {
                        if((p1+1)==p2)
                        {
                        printf("ERROR::filename can't be empty\n");
                        exit (0);
                        }
                        else
                        {  
                            char *p=strstr(s[i],"<");
                            p=strtok(p+1,">" );
                            char *r="/usr/include/";
                            char *rp=calloc(cc,sizeof(char));
                            strcpy(rp,r);
                            strcat(rp,p); //actual path
                            header_flag=1;
                            strcpy(replace[offset],rp); //copying the relative path to buffer.
                            a[offset]=i; //copying the line number in which the file need to include.
                            offset++;
                            FILE*fp=fopen(rp,"r");
                            if(fp==0)
                            {
                                printf("FATAL ERROR::No such file or directory\n");
                                exit (0);
                            }
                            fclose(fp);
                        }
                    }
                    else 
                    {
                    printf("ERROR::#include<header.h  no '>' character\n");
                    exit (0);
                    }
                }
                else
                {
                    printf("ERROR::#include @#$ <header.h>   charactor other than ' ' space found\n");
                    exit(0);
                }
                }
                else if(p1=strstr(s[i],"\""))
                {
                    l=k+8;
                while(s[i][l]!='"')
                {
                    if(s[i][l]==' ')
                    l++;
                    else
                    break;
                }
                if(s[i][l]=='"')
                {
                    int m=l;
                    if(p2=strstr(s[i]+l+1,"\""))
                    {
                        if((p1+1)==p2)
                        {
                        printf("ERROR::filename can't be empty\n");
                        exit (0);
                        }
                        else
                        {
                             char *p=strstr(s[i],"\"");
                            p=strtok(p+1,"\"" );


                            strcpy(replace[offset],p); //copying the actual path to buffer.
                            a[offset]=i; //copying the line number in which the file need to include.
                            FILE*fp=fopen(p,"r");
                            if(fp==0)
                            {
                            char *r="/usr/include/";
                            char *rp=calloc(cc,sizeof(char));
                            strcpy(rp,r);
                            strcat(rp,p); //actual path
                            strcpy(replace[offset],rp); //copying the relative path to buffer.
                            a[offset]=i; //copying the line number in which the file need to include.
                                FILE*fp=fopen(rp,"r");
                                if(fp==0)
                                {
                                printf("FATAL ERROR::No such file or directory\n");
                                exit (0);
                                }
                                fclose(fp);
                            }
                            header_flag=1;
                            offset++;
                        }
                    }
                    else
                    {
                    printf("ERROR::#include\"header.h  no '\"' character\n");
                    exit (0);
                    }
                }
                else
                {
                    printf("ERROR::#include @#$ \"header.h\"   charactor other than ' ' space found\n");
                    exit(0);
                }
                }
            }
        }  
    }
    offset=0;
    char file[100];
    strtok(argv,".");   //modifying the data in the stack of argv
    char *p=".i";
    strcat(argv,p);
    strcpy(file,argv);      //updated file name.  
    FILE*fp=fopen(file,"w");
    if(fp==0)
    {
        printf("ERROR creating the .i file\n");
        return ;
    }
    if(header_flag)
    {
    for(i=0;i<lc;i++)   
    {
        if(i==a[offset])
        {   
            FILE*hp=fopen(replace[offset],"r");
            if(hp==0)
            {
                printf("ERROR::Fail in opening the provided header file\n");
                return;
            }
            char ch;
            while((ch=fgetc(hp))!=EOF)
            fputc(ch,fp);
            offset++;
        }
        else
        {
            fputs(s[i],fp);
        }
    }
    }
    else
    {
        for(i=0;i<lc;i++)   
            fputs(s[i],fp);
    }
    filename=file;
    fclose(fp);
}
