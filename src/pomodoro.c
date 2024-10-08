#include "pomodoro.h"
#include "clock.h"
#include "pwd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"
#include "unistd.h"

void create_session_dir(void) {
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;

  char *safe_session_info_dir = malloc(1024);
  strcpy(safe_session_info_dir, (char *)homedir);
  strcat(safe_session_info_dir, "/.local/share/pom/");

  struct stat st = {0};
  if ((stat(safe_session_info_dir, &st) == -1)) {
    mkdir(safe_session_info_dir, 0777);
  }

  free(safe_session_info_dir);
  safe_session_info_dir = NULL;
}

void save_session_info(char *session_name, int session_number) {
  // Create session directory just in case
  create_session_dir();

  // Home directory stuff
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;

  char *safe_session_info_file = malloc(1024);
  strcpy(safe_session_info_file, (char *)homedir);
  strcat(safe_session_info_file, "/.local/share/pom/pomfile");

  FILE *file = fopen(safe_session_info_file, "r");
  if (file == NULL) {
    file = fopen(safe_session_info_file, "a+");
    fprintf(file, "session_name,session_number,date,time\n");
    fclose(file);
  }

  ptr_time time = get_time();

  FILE *f2 = fopen(safe_session_info_file, "a");
  fprintf(f2, "%s,%i,%s,%s\n", session_name, session_number, time.date,
          time.time);

  safe_session_info_file = NULL;
  free(safe_session_info_file);
}

void clear(void) {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

void pomodoro_session(char *session_name) {
  int session_counter = 1;
  pomo_timer on_state, pause_state;
  on_state.session_name = session_name;
  on_state.sec = 11; // This is 25 minutes
  on_state.state = on;
  on_state.current_session_number = 1;

  pause_state.session_name = session_name;
  pause_state.sec = 6; // this is 3 minutes
  pause_state.state = p_break;
  pause_state.current_session_number = 1;

  char opt;

  bool is_on = true;
  while (is_on == true) {
    pomo_countdown(on_state);

    char a;
    printf("\aProceed? [y/n]: ");
    scanf(" %c", &a);
    if (a == 'n') {
      break;
    }

    char b;
    pomo_countdown(pause_state);
    printf("\aProceed? [y/n]: ");
    scanf(" %c", &b);
    if (b == 'n') {
      break;
    }

    clear();

    on_state.current_session_number++;
    pause_state.current_session_number++;
    session_counter++;
  }

  save_session_info(session_name, session_counter);
}
