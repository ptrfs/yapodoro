#include "clock.h"
#include "stdio.h"
#include "time.h"

int pomo_countdown(unsigned int sec, enum pomo_state state) {
  /* Prints a countdown onto the screen. If the countdown fails,
   * it returns nonzero */

  while (sec > 0) {
    // Getting minutes
    int min = (sec / 60);
    int t_sec = (sec % 60);

    // Printing the current minutes or seconds left
    if (state == on) {
      printf("\r🍅 %02d:%02d", min, t_sec);
    } else if (state == p_break) {
      printf("\r🌹 %02d:%02d", min, t_sec);
    }

    // Making sure that the timer is always up-to-date
    fflush(stdout);

    // Clock synchronisation - Getting the current number of clock ticks since
    // the start of the function with `clock()`
    clock_t stop = clock() + CLOCKS_PER_SEC;

    // If stop is more than the clock ticks, stop the program for one second
    while (clock() < stop) {
    };

    // Decrement after a second has elapsed
    sec--;
  }

  return 0;
};
