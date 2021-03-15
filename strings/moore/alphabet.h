#pragma once
#include <stdlib.h>

#define alphabet_size 255

void init_alphabet_shift(const char *str, size_t len);
size_t get_alphabet_shift(char c);