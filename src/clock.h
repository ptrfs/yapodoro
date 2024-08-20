#pragma once

typedef struct ptr_time {
  char *date;
  char *time;
} ptr_time;

enum pomo_state {
  on,
  pause,
  p_break,
};

// Counting down functions
int pomo_countdown(unsigned int sec, enum pomo_state state);

// Getting time functions
ptr_time get_time();
