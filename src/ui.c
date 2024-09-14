#include "ui.h"
#include "color.h"
#include <stdlib.h>

void show_pomfile_info(ptr_csv_info info) {
  char *pomfile_rose = "💐";

  if (strtol(info.session_number, NULL, 10) < 2) {
    pomfile_rose = "🥀";
  } else if (strtol(info.session_number, NULL, 10) < 10) {
    pomfile_rose = "🌹";
  }

  printf(GRN " == %s pomodoro session == \n" reset, pomfile_rose);
  printf(CYN "Session name: " reset "%s\n", info.session_name);
  printf(CYN "Session number: " reset RED "%s\n" reset, info.session_number);
  printf(MAG "Date: " reset "%s - %s \n", info.date, info.time);
}
