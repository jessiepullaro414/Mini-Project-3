#include "types.h"
#include "user.h"

int main(int argc, char* argv[]) {

  printf(1, "ERROR???");
  printf("but this %p\n", *((int*)0));
  exit();
}
