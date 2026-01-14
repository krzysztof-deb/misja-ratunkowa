#ifndef _LOGGER_H
#define _LOGGER_H

void clear_file(const char *file_name);
void add_line_to_file(const char *file_name, int iteration, double best);


#endif