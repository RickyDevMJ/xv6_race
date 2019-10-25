#include "types.h"
#include "stat.h"
#include "user.h"

#define N 100

void
race_lock(void)
{
  int n, pid, c;

  counter_init();
  pid = fork(); 
  if(pid != 0)
  {
    sleep(10);
  }
  for(n=0;n<N;n++){
    my_lock();
    c = counter_get();
    counter_set(c+1);
    my_unlock();
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
  race_lock();
  exit();
}
