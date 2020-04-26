#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

#define PRIORITY_HIGH 99
#define PRIORITY_MIDDLE 50
#define PRIORITY_LOW 1
struct process{
	char name[33];
	int ready_time;
	int execute_time;
};

void execute_unit_time();
int execute_process(char* name, int execute_time, pid_t* pid, char* need_end_signal);
void set_priority(int pid, int priority_level);
