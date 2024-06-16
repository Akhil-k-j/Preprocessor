CC=cc
target=comment_replace.o header_check.o macro_check.o replacement.o main.o

my_preprocessor:${target}
		${CC} ${target} -o my_preprocessor

comment_replace.o:comment_replace.c
		${CC} -c comment_replace.c
header_check.o:header_check.c
		${CC} -c header_check.c		
macro_check.o:macro_check.c
		${CC} -c macro_check.c
replacement.o:replacement.c
		${CC} -c replacement.c
main.o:main.c
		${CC} -c main.c


clean:
	@rm -r *.o 
	@echo "clean up completed"
