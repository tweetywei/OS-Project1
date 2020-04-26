all:	FIFO SJF process scheduler

FIFO:
	gcc -O2 utils.h utils.c FIFO.c -o FIFO

SJF:
	gcc -O2 utils.h utils.c heap.h heap.c SJF.c -o SJF

process:
	gcc -O2 utils.h utils.c process.c -o process

scheduler:
	gcc -O2 utils.h utils.c main.c -o scheduler

clean:
	rm -f FIFO SJF process scheduler
