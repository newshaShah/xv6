#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int 
sys_getyear(void){
  return getyear();
}
int
sys_getChildren(void){
  return getChildren(myproc()->pid);
}
int 
sys_changePolicy(void){
    int policy;

  if(argint(0, &policy) < 0)
    return -1;
  return changePolicy(policy);
}

int 
sys_setPriority(void){
  int priority;
 
  if (argint(0,&priority)<0)
    return -1;
  

  return setPriority(priority);
}

int 
sys_waitForChild(void){

 int *creation_time;
  int *running_time;
  int *sleep_time;
  int *waiting_time;
  int *termination_time;
  argptr(0, (void *)&creation_time, sizeof(*creation_time));
  argptr(1, (void *)&running_time, sizeof(*running_time));
  argptr(2, (void *)&sleep_time, sizeof(*sleep_time));
  argptr(3, (void *)&waiting_time, sizeof(*waiting_time));
  argptr(4, (void *)&termination_time, sizeof(*termination_time));
  

 return waitForChild(creation_time,running_time,sleep_time,waiting_time,termination_time);
  


}
int setProcTimes(void){

  return setTimes();
  
}