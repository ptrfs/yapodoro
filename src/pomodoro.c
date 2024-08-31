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

  safe_session_info_dir = NULL;
  free(safe_session_info_dir);
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
    fprintf(file, "session_name,session_number\n");
    fclose(file);
  }

  FILE *f2 = fopen(safe_session_info_file, "a");
  fprintf(f2, "%s,%i\n", session_name, session_number);

  safe_session_info_file = NULL;
  free(safe_session_info_file);
}

// TODO: Actually do this function
void pomodoro(char *session_name) {
  int session_counter = 0;
  pomo_timer on_state, pause_state;
  on_state.session_name = session_name;
  on_state.sec = 1501;
  on_state.state = on;
  on_state.current_session_number = 0;

  pause_state.session_name = session_name;
  pause_state.sec = 301;
  pause_state.state = p_break;
  pause_state.current_session_number = 0;

  char opt;

  bool is_on = true;
  while (is_on == true) {
    pomo_countdown(on_state);

    char a;
    printf("Proceed? [y/n]: ");
    scanf(" %c", &a);
    if (a == 'n') {
      break;
    }

    char b;
    pomo_countdown(pause_state);
    printf("Proceed? [y/n]: ");
    scanf(" %c", &b);
    if (b == 'n') {
      break;
    }

    on_state.current_session_number++;
    pause_state.current_session_number++;
    session_counter++;
  }

  save_session_info(session_name, session_counter);
}
