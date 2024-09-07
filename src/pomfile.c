#include "pomfile.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

static const char *get_pomfile(void);

int count_lines(FILE *file) {
  char ch;
  int number = 1;

  if (file == NULL)
    return 0;

  while (!feof(file)) {
    if (ch == '\n') {
      number++;
    }
  }

  return number;
}

const char *getfield(char *line, int num) {
  const char *tok;
  for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
    if (!--num)
      return tok;
  }
  return NULL;
}

static const char *get_pomfile(void) {
  const char *home = getenv("HOME");
  char* m_pomfile_dir = malloc(1024);

  strcpy(m_pomfile_dir, home);
  strcat(m_pomfile_dir, "/.local/share/pomfile");

  return *m_pomfile_dir;

  free(m_pomfile_dir);
}

ptr_csv_info* m_get_csv_info(void) {
  FILE* file = fopen(get_pomfile, "r"); 
  if (file == NULL) return NULL;

  ptr_csv_info* csv = (ptr_csv_info*) malloc(count_lines(file) * sizeof(ptr_csv_info));
  if (csv == NULL) return NULL;

  rewind(file);

  for(int i = 2; i <= count_lines(file); i++) {
    char line[1024];
    while (fgets(line, 1024, file)) {
      char *tmp = strdup(line);
      csv[i].session_name = getfield(tmp, 1);
      csv[i].session_number = getfield(tmp, 2);
      csv[i].time = getfield(tmp, 3);
      csv[i].date = getfield(tmp, 4);
      free(tmp);
    }
  }

  fclose(file);
  return csv;
}

