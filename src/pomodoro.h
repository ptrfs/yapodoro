#pragma once

#include "stdbool.h"
#include "stdio.h"

void pomodoro_session(char *session_name);
void clear(void);
void create_session_dir(void);
void save_session_info(char *session_name, int session_number);
