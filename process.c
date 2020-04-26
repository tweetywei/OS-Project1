#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <sys/syscall.h>

int main(int argc, char* argv[]){
	fprintf(stderr, "some child process executing...\n");
	if(argc != 3){
		fprintf(stderr, "number of process parameter wrong!\n");
		exit(1);
	}
	pid_t pid = getpid();
	char name[33];
	int execute_time;
	strcpy(name, argv[1]);
	execute_time = atoi(argv[2]);
	printf("%s %ld\n", name, (long)pid);
	long start_sec, start_nsec;
	long end_sec, end_nsec;
	syscall(334, &start_sec, &start_nsec);
	for(int t = 0; t < execute_time; t++){
		execute_unit_time();
	}
	syscall(334, &end_sec, &end_nsec);
	syscall(335, pid, start_sec, start_nsec, end_sec, end_nsec);
	return 0;
}
