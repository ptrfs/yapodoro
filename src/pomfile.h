#pragma once
#include "stdio.h"


typedef struct ptr_csv_info {
  const char *session_name;
  const char *session_number;
  const char *date;
  const char *time;
} ptr_csv_info;

int count_lines(FILE *file);
char *getfield(char *line, int num);
const char *get_pomfile(void);
ptr_csv_info *m_get_csv_info(void);
