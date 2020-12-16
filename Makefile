CFLAGS:=-Wall -Wextra -Werror -I include

lab_05: obj/main.o obj/clist.o obj/point_list.o
	gcc obj/main.o obj/clist.o obj/point_list.o -o lab_05

obj: 
	mkdir obj

obj/main.o: src/main.c include/clist.h include/point_list.h | obj
	gcc -c $(CFLAGS) src/main.c -o obj/main.o

obj/clist.o: src/clist.c include/clist.h include/point_list.h | obj
	gcc -c $(CFLAGS) src/clist.c -o obj/clist.o

obj/point_list.o: src/point_list.c include/clist.h include/point_list.h
	gcc -c $(CFLAGS) src/point_list.c -o obj/point_list.o

.PHONY: clean
clean:
	rm -rf lab_05 obj