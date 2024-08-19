#pragma once

typedef struct ptr_time {
  char *date;
  char *time;
} ptr_time;

// Counting down functions
int countdown(unsigned int sec);
int countdown_min(unsigned int min);

// Getting time functions
ptr_time get_time();
