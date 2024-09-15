#pragma once
#include "pomfile.h"

enum pomfile_show_type { verbose, oneline };

void show_pomfile_info(ptr_csv_info info, enum pomfile_show_type type);
void print_all_info(void);
