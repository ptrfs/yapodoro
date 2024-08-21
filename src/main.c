#include "clock.h"
#include <stdio.h>

int main() {
  ptr_time time = get_time();
  printf("%s, %s\n", time.time, time.date);
}
