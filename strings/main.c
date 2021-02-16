#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>    
#include <unistd.h>
#include <sys/mman.h>
#include "alphabet.h"

bool is_suffix(const char *text, int len, int from, int suffix)
{
    while (suffix < len)
    {
        if (text[from++] != text[suffix++]) {
            return false;
        }
    }

    return true;
}

int *suffix_shift(const char* template, size_t len)
{
    int *data = malloc(len*sizeof(int)); 
    if (!data) return NULL;

    for (size_t i = 0; i < len; i++)
    {
        size_t idx = len - i - 1;
        int suffix = 1;
        for (size_t j = 0; j < idx; j++) 
        {
            if (is_suffix(template, len, j, idx))
            {
                suffix = len - (len - idx) - j;
            }
        }
        if (suffix == 1 && i != 0) {
            suffix = len - 1;
        }
        data[i] = suffix;
    }

    return data;   
}

int boyer_moore(const char *str, const char *template)
{
    size_t str_len = strlen(str);
    size_t template_len = strlen(template);
    if (template_len == 0 || template_len > str_len) return -1;

    init_alphabet_shift(template, template_len);
    int *suffix = suffix_shift(template, template_len);
    if (suffix == NULL) return -1;

    size_t begin = 0;
    while (begin + template_len - 1 < str_len)
    {
        int match = template_len - 1;
        while (match >= 0 && template[match] == str[begin+match])
        {
            match--;
        }

        if (match == -1) 
        {
            return begin;
        }
           
        begin += (match == template_len-1) ? get_alphabet_shift(str[begin+match]) : suffix[template_len - match];
    }
    
    return -1;
}


int main()
{
    return EXIT_SUCCESS;
}