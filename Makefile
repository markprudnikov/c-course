CFLAGS:=-Wall -Wextra -Werror -I include

lab_04: obj/main.o obj/clist.o
	gcc obj/main.o obj/clist.o -o lab_04

obj: 
	mkdir obj

obj/main.o: src/main.c include/clist.h | obj
	gcc -c $(CFLAGS) src/main.c -o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -c $(CFLAGS) src/clist.c -o obj/clist.o

.PHONY: clean
clean:
	rm -rf lab_04 obj