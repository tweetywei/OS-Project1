#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/ktime.h>

asmlinkage void sys_get_time(long* sec, long* nsec)
{
    struct timespec t;
    getnstimeofday(&t);
    printk("[test time] %ld %ld\n", t.tv_sec, t.tv_nsec);
    (*sec) = (long)t.tv_sec;
    (*nsec) = (long)t.tv_nsec;
    return;
}
