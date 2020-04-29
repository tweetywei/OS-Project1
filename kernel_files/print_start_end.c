#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_print_start_end(int pid, long start_sec, long start_nsec, long end_sec, long end_nsec)
{
    printk("[Project1] %d %ld.%09ld %ld.%09ld\n", pid, start_sec, start_nsec, end_sec, end_nsec);
  
    return;
}
