#include "pomodoro.h"
#include "clock.h"
#include "dirent.h"
#include "pwd.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"
#include "unistd.h"

static const char *getfield(char *line, int num) {
  const char *tok;
  for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
    if (!--num)
      return tok;
  }
  return NULL;
}

static int get_file_lines(FILE *file) {
  int lines = 0;
  char ch;

  if (file == NULL) {
    return -1;
  }

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n')
      lines++;
  }

  return lines;
}

static bool find_directory(char *dir_name) {
  DIR *temp = opendir(dir_name);
  if (temp == NULL) {
    return true;
  } else {
    return false;
  }
}

static FILE *setup_pomodoro_session_file(char *session_name) {
  // Giving session_name space to work with
  char session_name_with_space[4096];
  strcpy(session_name_with_space, session_name);

  // Start by writing the session name into the sessions file
  struct passwd *pwd = getpwuid(getuid());
  char *home_dir = pwd->pw_dir;
  char *dir = malloc(1024);
  FILE *file;

  strcpy(dir, home_dir);
  strcat(dir, "/.local/pom/");

  if (!find_directory(dir)) {
    int mk_r = mkdir(dir, 0700);
    if (mk_r == -1)
      return NULL;
  }

  char *pomfile = malloc(1024);
  strcpy(pomfile, dir);
  strcat(pomfile, "/pomfile");

  file = fopen(pomfile, "a+");
  if (file == NULL) {
    pomfile = NULL;
    free(pomfile);

    dir = NULL;
    free(dir);

    return NULL;
  }

  ptr_time current_time = get_time();
  char *fulltime = malloc(1024);

  sprintf(fulltime, "%s, %s", current_time.date, current_time.time);

  strcat(session_name_with_space, ";");
  strcat(session_name_with_space, fulltime);

  int fput_res = fputs(session_name_with_space, file);
  if (fput_res == EOF)
    return NULL;

  dir = NULL;
  free(dir);

  pomfile = NULL;
  free(pomfile);

  fulltime = NULL;
  free(fulltime);

  return file;
}

int pomodoro(char *session_name) {
  FILE *file = setup_pomodoro_session_file(session_name);
  if (file == NULL) {
    return -1;
  }
}
