#include"header.h"

extern int lc;
extern char **s;
extern int cc;
extern char *filename;

extern int mc;
extern char **mreplace2;
extern char **mreplace1;
extern int *m_line;
int *skip_mline;
int skip_mline_count;

void macro_replacement(char *argv)
{
        int i=0;
        int x=0;
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
                        x++;
                }
            }
        }
        //for(i=0;i<lc;i++)
        //printf("%s",s[i]);
        x=0;
        int y=0;
        FILE *fp=fopen(argv,"w");
        if(fp==0)
        {
            printf("ERROR::Unable to open the final file for modification\n");
            return ;
        }
        if(mc==0 && skip_mline_count==0)
        {
            for(i=0;i<lc;i++)
            fputs(s[i],fp);
            return ;
        }
        else
        {
            for(i=0;i<lc;i++)
            {
                if(i==m_line[x])
                {
                    fputc('\n',fp);
                    x++;
                }
                else if(skip_mline_count!=0)
                {
                if(i==skip_mline[y])
                {
                    fputc('\n',fp);
                    y++;
                }
                }
                else
                  fputs(s[i],fp);
            }
            return ;
        }
}