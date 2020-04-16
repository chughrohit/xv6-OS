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

//hello
int
sys_hello(void)
{
  print_hello();
  return 0;
}

//lab1-info
int
sys_info(void)
{
  int val;
  argint(0, &val);
  
  struct proc *curr_proc;
  curr_proc = myproc();

  if(val == 1)
  {
    cprintf("Number of Processes: %d\n", info(val));
  }

  else if(val == 2)
  {
    cprintf("Number of System Calls: %d\n", curr_proc->num_sys_calls);
  }

  else if(val == 3)
  {
    cprintf("Number of Memory Page: %d\n", (int)(curr_proc->sz)/PGSIZE);
  }

  else
  {
    cprintf("Invalid Parameter Value.\n");
  }

  return 0;
}
