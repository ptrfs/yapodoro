#pragma once
#include "stdio.h"

int count_lines(FILE *file);

typedef struct ptr_csv_info {
  char* session_name;
  char* session_number;
  char* date;
  char* time;
} ptr_csv_info;

ptr_csv_info* get_csv_info(void);

