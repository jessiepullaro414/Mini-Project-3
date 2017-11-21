#include "types.h"
#include "user.h"

/*int
main (int argc, char* argv[])
{
  int ppid = getpid();
  int pid = fork();
  if (pid < 0) {
    printf(1, "TEST FAILED\n");
    exit();
  }
  else if (pid == 0) {
    uint* nullp = (uint*)0;
    printf(1, "null dereference: ");
    printf(1, "%x %x\n", nullp, *nullp);
    // this process should be killed
    printf(1, "TEEST FAILED\n");
    kill(ppid);
    exit();
  }
  else {
    wait();
    printf(1, "TEST PASSED\n");
    exit();
  }
}*/



/*int
main(int argc, char* argv[])
{
  int ppid = getpid();
  int pid = fork();
  if (pid < 0) {
    printf(1, "TEST FAILED\n");
    exit();
  }
  else if (pid == 0) {
    uint* badp = (uint*)4095;
    printf(1, "bad dereference (0x0fff): ");
    printf(1, "%x %x\n", badp, *badp);
    // this process should be killed
    printf(1, "TEST FAILED\n");
    kill(ppid);
    exit();
  }
  else {
    wait();
  }
}*/


//#include <assert.h>
void assert(uint condition)
{
  if (!condition) printf(1, "Failed test\n");
}

#include "fcntl.h"

/*int main(int argc, char* argv[])
{
  char *arg;

  int fd = open("tmp", O_WRONLY|O_CREATE);
  assert(fd != -1);

  // at zero
  arg = (char*) 0x0;
  assert(write(fd, arg, 10) == -1);

  // within null page
  arg = (char*) 0x400;
  assert(write(fd, arg, 1024) == -1);
  // spanning null page and code
  arg = (char*) 0xfff;
  assert(write(fd, arg, 2) == -1);
  printf(1, "TEST PASSED\n");
  exit();
}*/


void test_failed()
{
  printf(1, "FAILED :(\n");
}

void test_passed()
{
  printf(1, "PASSED :)\n");
}


/*int main (int argc, char* argv[])
{
  void *ptr;
  ptr = sharedmem_access(-1);
  if (ptr != NULL) {
    test_failed();
  }

  ptr = sharedmem_access(-100);
  if (ptr != NULL) {
    test_failed();
  }

  ptr = sharedmem_access(4);
  if (ptr != NULL) {
    test_failed();
  }

  ptr = sharedmem_access(100);
  if (ptr != NULL) {
    test_failed();
  }

  test_passed();
  exit();
}*/

/*int main (int argc, char* argv[])
{
  int n;
  int i;

  for (i = 0; i < 4; i++) {
     n = sharedmem_count(i);
     if (n != 0) {
       test_failed();
     }
  }
  test_passed();
  exit();
}*/
/*
int
main(int argc, char* argv[])
{
  char* ptr;
  int i;
  for (i = 3; i >= 0; i--) {
    printf(1, "i=%d\n", i);
    ptr = sharedmem_access(i);
    if (ptr == NULL) {
      test_failed();
    }
    *ptr = 'c';
  }
  test_passed();
  exit();
}
*/
#define USERTOP 0xA0000 // end of user address space

/*int main(int argc, char* argv[])
{
  char *ptr;
  int i;

  ptr = sharedmem_access(3);
  if (ptr == NULL) test_failed();

  char arr[4] = "tmp";
  for (i = 0; i < 4; i++) {
    *(ptr+i) = arr[i];
  }

  //argstr
  int fd = open(ptr, O_WRONLY|O_CREATE);
  if (fd == -1) {
    printf(1, "open system call faeild to take a string from within a shared page\n");
    test_failed();
  }

  //argptr
  int n = write(fd, ptr, 10);
  if (n == -1) {
    printf(1, "write system call failed to take a pointer from within a shared page\n");
    test_failed();
  }

  //making sure invalid strings are still caught
  int fd2 = open((char *)(USERTOP/2), O_WRONLY|O_CREATE);
  if (fd2 != -1) {
    printf(1, "open system call successfully accepted an invalid string\n");
    test_failed();
  }

  //making sure invalid pointers are still caught
  n = write(fd, (char *) (USERTOP/2), 10);
if (n != -1) {
    printf(1, "write system call successfully accepted an invalid pointer\n");
    test_failed();
  }

  //making sure edge case is checked
  n = write(fd, (char*)(ptr+4094), 10);
  if (n != -1) {
    printf(1, "write system call successfully accepted an overflowing pointer in a shared page\n");
    test_failed();
  }

   test_passed();
   exit();
 }
/*int
main (int argc, char* argvp[])
{
  int n;
  n = sharedmem_count(-1);
  if (n!= -1) test_failed();
  n = sharedmem_count(-100);
  if (n!=-1) test_failed();
  n = sharedmem_count(4);
  if (n!=-1) test_failed();
  n = sharedmem_count(100);
  if (n!= -1) test_failed();
  test_passed();
  exit();
}*/

/*int main(int argc, char* argv[])
{
  void *ptr;
  int n;
  int i;
  for (i = 0; i < 4; i++) {
    ptr = sharedmem_access(i);
    if (ptr == NULL) test_failed();
    n  = sharedmem_count(i);
    if (n!=1) test_failed();
  }
  test_passed();
  exit();
}*/

/*int main(int argc, char* argv[])
{
  void *ptr;
  int n;
  int i;
  for(i = 0; i < 4; i++) {
    ptr = sharedmem_access(i);
    if (ptr == NULL) test_failed();
    ptr = sharedmem_access(i);
    if (ptr == NULL) test_failed();
    n = sharedmem_count(i);
    if (n!= 1) test_failed();
  }
  test_passed();
  exit();
}*/

int main(int argc, char* argv[])
{
  void *ptr;
  int n;
  int i;
  for (i = 0; i < 4; i++) {
    ptr = sharedmem_access(i);
    if (ptr == NULL) test_failed();
  }
  int pid = fork();
  if (pid < 0) {
    test_failed();
  } else if (pid == 0) {
    for (i = 0; i < 4; i++) {
      n = sharedmem_count(i);
      if (n != 2) test_failed();
    }
  } else {
    wait();
  }

 test_passed();
 exit();
 }
