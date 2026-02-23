#include "types.h"
#include "stat.h"
#include "user.h"

static volatile int sink = 0;
static void burn(int n){ for(int i=0;i<n;i++) sink += i; }

int main(int argc, char **argv){
  // Test 1: validate settickets
  if(settickets(0) == 0){
    printf(1, "FAIL: settickets(0) should fail\n");
    exit();
  }
  if(settickets(10) != 0){
    printf(1, "FAIL: settickets(10) should succeed\n");
    exit();
  }
  printf(1, "PASS: settickets validation\n");

  // Test 2: fork two children with 1 vs 3 tickets
  // Expected CPU ratio ~1:3
  int pid1 = fork();
  if(pid1 == 0){
    settickets(1);
    for(int k=0;k<200;k++) burn(200000);
    printf(1, "child1 (1 ticket) done\n");
    exit();
  }

  int pid2 = fork();
  if(pid2 == 0){
    settickets(3);
    for(int k=0;k<200;k++) burn(200000);
    printf(1, "child2 (3 tickets) done\n");
    exit();
  }

  wait();
  wait();
  printf(1, "testlottery: done\n");
  exit();
}