#include"header.h"
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

    comment_replace(argv[1]);    //Error checks and comment removals

    macro_check(argv[1]);        //Error checks and data storage in buffer
    
    header_check(argv[1]);       //Error checks and data storage in buffer
    
    //PROCEED TO MACRO AND HEADER REPLACE AFTER THE ERROR CHECKS
    replacement(argv[1]); 
    //1) MACRO REPLACED WITHIIN THE CREATED BUFFER
    //2) HEADER FILE INCLUDED BASED ON THE LINE NUMBER.
}
