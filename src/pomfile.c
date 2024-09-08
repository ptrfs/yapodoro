#include "pomfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count_lines(FILE *file) {
  char ch;
  int number = 0;

  if (file == NULL)
    return 0;

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      number++;
    }
  }

  // Add one more line if the file is not empty and does not end with a newline
  if (ftell(file) > 0 && ch != '\n') {
    number++;
  }

  rewind(file); // Reset file position to beginning
  return number;
}

char *getfield(char *line, int num) {
  const char *tok;
  for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
    if (--num == 0) {
      return tok;
    }
  }
  return NULL;
}

const char *get_pomfile(void) {
  const char *home = getenv("HOME");
  if (home == NULL)
    return NULL;

  char *m_pomfile_dir =
      malloc(strlen(home) + strlen("/.local/share/pomfile") + 1);
  if (m_pomfile_dir == NULL)
    return NULL;

  strcpy(m_pomfile_dir, home);
  strcat(m_pomfile_dir, "/.local/share/pomfile");

  return m_pomfile_dir; // Return the allocated string
}

ptr_csv_info *m_get_csv_info(void) {
  const char *pomfile_path = get_pomfile();
  if (pomfile_path == NULL)
    return NULL;

  FILE *file = fopen(pomfile_path, "r");
  if (file == NULL) {
    free((void *)pomfile_path); // Free memory for the path
    return NULL;
  }

  int lines = count_lines(file);
  ptr_csv_info *csv = (ptr_csv_info *)malloc(lines * sizeof(ptr_csv_info));
  if (csv == NULL) {
    fclose(file);
    free((void *)pomfile_path); // Free memory for the path
    return NULL;
  }

  rewind(file); // Reset file pointer to beginning

  for (int i = 0; i < lines; i++) {
    char line[1024];
    if (fgets(line, sizeof(line), file)) {
      char *tmp = strdup(line);
      if (tmp != NULL) {
        csv[i].session_name = getfield(tmp, 1);
        csv[i].session_number = getfield(tmp, 2);
        csv[i].time = getfield(tmp, 3);
        csv[i].date = getfield(tmp, 4);
        free(tmp);
      }
    }
  }

  fclose(file);
  free((void *)pomfile_path); // Free memory for the path
  return csv;
}
