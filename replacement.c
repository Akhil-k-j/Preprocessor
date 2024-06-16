#include"header.h"

///actual file data//// 
extern char **s;
extern int lc;
extern int cc;

///Macro related datas/////
extern int mc;
extern char **mreplace2;
extern char **mreplace1;
extern int *m_line;
extern int *skip_mline;
extern int skip_mline_count;

///Header related data's///
extern int header_flag;
extern char **replace;
extern int* a;

void replacement(char *argv)   //This argv is argv[1]  at the sending end. There for we get the actual filename
{           
        int i=0,x=0;  //see below explanation
        if(mc!=0)
        {
            for(i=0;i<lc;i++)
            {
                if(i==m_line[x])
                {
                        int j;
                        //int k=i;
                        char *sb;
                        int sn=strlen(mreplace1[x]);
                        for(j=i+1;j<lc;j++)
                        {
                            L1:
                            if(sb=strstr(s[j],mreplace1[x]))
                            {
                                char *p=calloc(cc,sizeof(char));   //if repeated,then the word again need to change. inside LABEL L1 make sure every time we get new memory with 0 initialized.
                                char *a=calloc(cc,sizeof(char));  // above reason.
                                strcpy(a,mreplace2[x]);//logic
                                strncpy(p,s[j],sb-s[j]);  //logic
                                strcat(a,sb+sn);                      //Logic
                                strcat(p,a);//logic
                                strcpy(s[j],p);         //updated string with null in the remaining bytes.
                                if(strstr(s[j],mreplace1[x]))   //copying the final updated string to s[i].
                                goto L1;
                            }
                        }
                        x++;   //to get the next macro and macro definition once the current macro is replaced in the same and all remaining line.
                }
            }
        }

//By now all the macro is replaced inside the buffer, Now header file inclusion is pending.

//////////////////////Required file name//////////////////////////

    //ARGV in the below line is actual file name (see the argument of the function call to this function its->argv[1])
    char file[100];
    strtok(argv,".");   //modifying the data in the stack of argv
    char *p=".i";
    strcat(argv,p);    //argv=> updated/required file name wtih .i extension

/////////////////////////WRITING///////////////////////////////
       x=0;
       int y=0;
       int z=0;

        FILE *fp=fopen(argv,"w");
        if(fp==0)
        {
            printf("ERROR::Unable to open the final file for modification\n");
            return ;
        }

        for(i=0;i<lc;i++)         //In this single loop we will monitor which line to copy based on the condition
        {
            if(header_flag==1)
            {
                if(i==a[z])
                {   
                    FILE*hp=fopen(replace[z],"r");
                    if(hp==0)
                    {
                    printf("ERROR::Fail in opening the provided header file\n");
                    return;
                    }
                    char ch;
                    while((ch=fgetc(hp))!=EOF)
                    fputc(ch,fp);                      //Cpying the header file content character by character
                    z++;
                    continue;   //If true(Why need to check the remaining condition?)
                }
            }
            if(mc!=0)
            {
                if(i==m_line[x])
                {
                    fputc('\n',fp);      //that purticular macro line should be kept blank  //blank logic (eg #define PI 3.14)
                    x++;                  //Macro array increment (at end,array contain 0, so i becomes 0 ,so if wont execute)
                    continue;    //If true(Why need to check the remaining condition?)
                }
            }
            if(skip_mline_count!=0)
            {
                if(i==skip_mline[y])
                {
                    fputc('\n',fp);  //that purticular macro line should be kept blank  //blank line logic (eg #define SKIP) 
                    y++;        //skip line array stored incremented(at last it becomes to 0, so i becomes zero thus if wont execute)
                    continue;    //If true(Why need to check the remaining condition?)
                }
            }
            fputs(s[i],fp);    //IMPORTANT!!   updated line (maybe with macro or wihtout macro) copied to the file from the updated buffer.
        }

        fclose(fp);  //IMPORTANT!!  (For safer side) else it wont reflect in the internal buffer of FILE * (sometimes)
}
