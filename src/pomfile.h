#pragma once
#include "stdio.h"

int count_lines(FILE *file);

typedef struct ptr_csv_info {
  const char *session_name;
  const char *session_number;
  const char *date;
  const char *time;
} ptr_csv_info;

ptr_csv_info *get_csv_info(void);
