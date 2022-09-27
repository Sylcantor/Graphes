all: mst.out

mst.out: main.o wgraph.o wnodelist.o utility.o
	gcc -Wextra -Wall -O3 main.o wgraph.o wnodelist.o utility.o -o mst.out

main.o: main.c wnodelist.h wgraph.h utility.h
	gcc -Wextra -Wall -O3 -c main.c -o main.o

utility.o: utility.h utility.c
	gcc -Wextra -Wall -O3 -c utility.c -o utility.o

wgraph.o: wgraph.h wgraph.c utility.h wnodelist.h
	gcc -Wextra -Wall -O3 -c wgraph.c -o wgraph.o

wnodelist.o: wnodelist.h wnodelist.c utility.h
	gcc -Wextra -Wall -O3 -c wnodelist.c -o wnodelist.o

clean:
	rm *.o

veryclean: clean
	rm *.out

