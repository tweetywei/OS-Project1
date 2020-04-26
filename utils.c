#include "utils.h"


void execute_unit_time(){
	volatile unsigned long i; for(i=0;i<1000000UL;i++); 
}

int execute_process(char* name, int execute_time, pid_t* pid, char* need_end_signal){
	pid_t parent_pid = getpid();
	char parent_pid_str[15];
	sprintf(parent_pid_str, "%d", (int)parent_pid);
	(*pid) = fork();
	char execute_time_str[15];
	cpu_set_t set_cpu_mask;
	CPU_ZERO(&set_cpu_mask);
	CPU_SET(1, &set_cpu_mask);
    switch(*pid){
		case -1:
			fprintf(stderr, "child fork error\n");
			exit(-1);
		case 0:
			sched_setaffinity(getpid(), sizeof(cpu_set_t), &set_cpu_mask);
			sprintf(execute_time_str, "%d", execute_time);
			execl("./process", "./process", name, execute_time_str, parent_pid_str, need_end_signal, (char *)0);
			break;
		default:
			set_priority((*pid), PRIORITY_LOW);
			fprintf(stderr, "child pid is %d\n", (*pid));
			break;
    }
}

void set_priority(pid_t pid, int priority_level){
	struct sched_param param;
	param.sched_priority = priority_level;
	fprintf(stderr, "set pid = %d to %d\n", (int)pid, priority_level);
	fflush(stderr);
	if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1){
            fprintf(stderr, "set priority wrong, pid is %d, err = %s?\n", pid, strerror(errno));
            exit(1);
     }
}
