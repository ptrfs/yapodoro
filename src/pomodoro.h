#pragma once

#include "stdbool.h"
#include "stdio.h"

// Getting file info
const char *getfeild(char *line, int num);
int get_file_lines(FILE *file);

// Directory traversal
bool find_directory(char *dir_name);

// pomfile stuff
FILE *setup_pomodoro_session_file(char *session_name);
int populate_pomfile(FILE *file, char *session_name);

// Actual pomodoro session stuff
int pomodoro(char *session_name);
