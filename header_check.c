#include"header.h"

extern int lc;
extern char **s;
extern int cc;

////////Header related files//////////
char **replace;     //header replace location(Either std liibrary path or relative path) saved in this 2D buffer
int *a;              //header line number stored
int header_flag=0;   //By default considering there is no any header file to add.
/////////////////////////////////////

void header_check(char *argv)
{
    int i=0;
    int offset=0;
    char *p1,*p2;
    int flag1=0,flag2=0;

    //creating buffer and array to store the line where the Header inclusion take place and also the header file path.
    a=calloc(lc,sizeof(int));     //for storing the line of header file inclusion
    
    replace=calloc(lc,sizeof(int*));
    for(i=0;i<lc;i++)
    replace[i]=calloc(cc,sizeof(char));  //for storing the header file path

    //checking for header file inclusion.
    for(i=0;i<lc;i++)
    {
        if(p1=strstr(s[i],"#include"))
        {
            int j=0;
            while(s[i][j]!='#')   //$  <space>     #include<stdio.h>
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
                if(p1=strstr(s[i],"<"))    //for std lib file
                {
                    l=k+8;
                while(s[i][l]!='<')      //#include      <stdio.h>
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
                        if((p1+1)==p2)          //#incldue<>
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
                            strcpy(replace[offset],rp);     //copying the relative path to buffer.
                            a[offset]=i;                    //copying the line number in which the file need to include.
                            offset++;                       //updating for the next incoming same did in relative path also.
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
                else if(p1=strstr(s[i],"\""))  //For relative directory
                {
                    l=k+8;
                while(s[i][l]!='"')
                {
                    if(s[i][l]==' ')
                    l++;
                    else
                    break;
                }
                if(s[i][l]=='"')   //#include     ->"header.h"
                {
                    int m=l;
                    if(p2=strstr(s[i]+l+1,"\""))   //searching for the second '"'
                    {
                        if((p1+1)==p2)         //#include ""
                        {
                        printf("ERROR::filename can't be empty\n");
                        exit (0);
                        }
                        else
                        {
                             char *p=strstr(s[i],"\"");
                            p=strtok(p+1,"\"" );  //extracting the exact location


                            strcpy(replace[offset],p);     //copying the actual path to buffer.
                            a[offset]=i;                   //copying the line number in which the file need to include.
                            FILE*fp=fopen(p,"r");        //Checking the current path opening succesfully or not.
                            if(fp==0)       //If not found in the current path need to check the std library path. (FIRST always need to check the current path.)
                            {
                            char *r="/usr/include/";
                            char *rp=calloc(cc,sizeof(char));
                            strcpy(rp,r);
                            strcat(rp,p); //actual path

                            strcpy(replace[offset],rp); //copying the relative path to buffer.
                            a[offset]=i; //copying the line number in which the file need to include.
                            
                                FILE*fp=fopen(rp,"r");         
                                if(fp==0)          //If not available in the std library path also, Then error
                                {
                                printf("FATAL ERROR::No such file or directory\n");
                                exit (0);
                                }
                                fclose(fp);
                            }
                            header_flag=1;
                            offset++;                   //updating for the next incoming
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
}