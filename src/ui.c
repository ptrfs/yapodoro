#include "ui.h"
#include "color.h"
#include "pomfile.h"
#include <stdio.h>
#include <stdlib.h>

static int strtoi(const char *input) {
  int res = 0;
  scanf(input, "%d", &res);
  return res;
}

void show_pomfile_info(ptr_csv_info info, enum pomfile_show_type type) {
  char *pom_flower = "🥀";

  if (strtoi(info.session_number) > 2 && strtoi(info.session_number) < 10) {
    pom_flower = "🌹";
  } else if (strtoi(info.session_number) < 10) {
    pom_flower = "💐";
  }

  if (type == verbose) {
    printf(GRN "%s: %s \n Sessions: %s \n Date: %s-%s \n" reset, pom_flower,
           info.session_name, info.session_number, info.date, info.time);
  }

  printf(GRN "%s - %s: %s Sessions on %s at %s" reset, pom_flower,
         info.session_name, info.session_number, info.date, info.time);
}

void print_all_info(void) {
  ptr_csv_info *info = m_get_csv_info();
  int info_size = sizeof(*info);

  for (int i = 0; i <= info_size; i++) {
    show_pomfile_info(info[i], verbose);
  }

  free((void *)info);
}
