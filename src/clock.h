#pragma once

typedef struct ptr_time {
  char date[33];
  char time[6];
} ptr_time;

enum pomo_state {
  on,
  p_pause,
  p_break,
};

typedef struct pomo_timer {
  unsigned int sec;
  enum pomo_state state;
  int current_session_number;
  char *session_name;
} pomo_timer;

// Counting down functions
int pomo_countdown(pomo_timer timer);

// Getting time functions
ptr_time get_time(void);
