#include <stdlib.h>
#include "alphabet.h"

#define alphabet_size 255

static size_t alphabet_shift[alphabet_size] = {0};

size_t get_shift(char c)
{
    return alphabet_shift[c];
}

void init_alphabet_shift(const char *str, size_t len)
{
    for (size_t i = 0; i < alphabet_size; ++i) alphabet_shift[i] = len;
    for (size_t i = 0; i < len-1; ++i)
    {
        alphabet_shift[str[i]] = len - i - 1;
    }
}

