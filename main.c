#include"header.h"
char **s;
int lc;
int cc;
char **replace;
char *a;
char *filename;

int mc;
char **mreplace2;
char **mreplace1;
int *m_line;


int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("usage::./my_Preprocessor filename.c\n");
        return 0;
    }
    if(!strstr(argv[1],".c"))
    {
        printf("ERROR::Preproccossor only supported .c files\nm");
        return 0;
    }
    comment_replace(argv[1]);
    header_replace(argv[1]);
    macro_check(argv[1]);
    macro_replacement(argv[1]);
}
