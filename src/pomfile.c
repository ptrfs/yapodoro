#include "pomfile.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

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

static const char *get_home_name(void) {
  const char *home = getenv("HOME");
  return home;
}

// ptr_csv_info *m_get_csv_info(void) {
//   char *safe_csv_dir = malloc(1024);
//   strcpy(safe_csv_dir, "/home/");
//   strcat(safe_csv_dir, get_home_name());
//   strcat(safe_csv_dir, "/.local/share/pom/pomfile");

//   FILE *file = fopen(safe_csv_dir, "r");
//   int line_num = count_lines(file);
//   ptr_csv_info *csv;
//   csv = (ptr_csv_info *)malloc(line_num * sizeof(ptr_csv_info));
//   if (csv == NULL) {
//     return NULL;
//   }
// }
