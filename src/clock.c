#include "clock.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

char *months[] = {"January",   "February", "March",    "April",
                  "May",       "June",     "July",     "August",
                  "September", "October",  "November", "December"};

int pomo_countdown(pomo_timer timer) {
  /* Prints a countdown onto the screen. If the countdown fails,
   * it returns nonzero */

  while (timer.sec > 0) {
    // Getting minutes
    int min = (timer.sec / 60);
    int t_sec = (timer.sec % 60);

    // Printing the current minutes or seconds left
    if (timer.state == on) {
      printf("\r🍅 Session #%d: %s - %02d:%02d", timer.current_session_number,
             timer.session_name, min, t_sec);
    } else if (timer.state == p_break) {
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
    timer.sec--;
  }

  return 0;
}

ptr_time get_time(void) {
  time_t t1, t3;
  struct tm *t2;

  t1 = time(NULL);
  t2 = localtime(&t1);

  ptr_time result;

  if (t2 == NULL) {
    strcpy(result.time, "0000");
    return result;
  }

  // Getting Hour
  char hr[6];
  sprintf(hr, "%02d", t2->tm_hour);

  // Adding minute
  char min[6];
  sprintf(min, ":%02d", t2->tm_min);

  // Pushing hour and min together
  strcat(hr, min);
  strcpy(result.time, hr);

  // Getting day
  char day[32];
  sprintf(day, "%02d ", t2->tm_mday);

  // Getting month
  char month[12];
  sprintf(month, "%s", months[t2->tm_mon]);

  // Pushing day and month together
  strcat(day, month);
  strcpy(result.date, day);

  return result;
}
