#include "types.h"
#include "stat.h"
#include "user.h"

#define N 10000

void
race_futex(void)
{
  int n, pid, c, t1, t2;

  counter_init();
  t1 = uptime();
  pid = fork(); 
  
  for(n=0;n<N;n++){
    my_futex_lock();
    c = counter_get();
    counter_set(c+1);
    my_futex_unlock();
  }

  if(pid > 0)
  {
    wait();
    t2 = uptime();
    printf(1, "Time taken = %d\n", t2-t1);
  }
  printf(1,"%d\n",counter_get());
}

int
main(void)
{
  race_futex();
  exit();
}
