#include "types.h"
#include "stat.h"
#include "user.h"

#define N 10000

void
race_f_lock(void)
{
  int n, pid, c;

  counter_init();
  pid = fork(); 
  
  for(n=0;n<N;n++){
    my_f_lock();
    c = counter_get();
    counter_set(c+1);
    my_f_unlock();
  }

  if(pid > 0)
  {
    wait();
  }
  printf(1,"%d\n",counter_get());
}

int
main(void)
{
  race_f_lock();
  exit();
}
