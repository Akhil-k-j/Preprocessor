CC=cc
target=comment_replace.o header_replace.o macro_check.o macro_replacement.o main.o

my_preprocessor:${target}
		${CC} ${target} -o my_preprocessor

comment_replace.o:comment_replace.c
		${CC} -c comment_replace.c
header_replace.o:header_replace.c
		${CC} -c header_replace.c		
macro_check.o:macro_check.c
		${CC} -c macro_check.c
macro_replacement.o:macro_replacement.c
		${CC} -c macro_replacement.c
main.o:main.c
		${CC} -c main.c


clean:
	@rm -r *.o 
	@echo "clean up completed"
