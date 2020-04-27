all:	FIFO SJF PSJF RR process scheduler

FIFO:
	gcc -O2 utils.h utils.c FIFO.c -o FIFO

SJF:
	gcc -O2 utils.h utils.c heap.h heap.c SJF.c -o SJF

PSJF:
	gcc -O2 utils.h utils.c heap.h heap.c PSJF.c -o PSJF

RR:
	gcc -O2 utils.h utils.c queue.h queue.c RR.c -o RR

process:
	gcc -O2 utils.h utils.c process.c -o process

scheduler:
	gcc -O2 utils.h utils.c main.c -o scheduler

clean:
	rm -f FIFO SJF PSJF RR process scheduler
