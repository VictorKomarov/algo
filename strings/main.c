#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>    
#include <unistd.h>
#include <sys/mman.h>
#include "alphabet.h"

int boyer_moore(const char *str, const char *template)
{
    size_t str_len = strlen(str);
    size_t template_len = strlen(template);
    if (template_len == 0 || template_len > str_len) return -1;

    init_alphabet_shift(template, template_len);

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
        
        begin += get_shift(str[begin+match]);
    }
    
    return -1;
}

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

int *suffix_shift(const char* template)
{
    size_t len = strlen(template);
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

int main()
{
    const char *template = "AB..B..AB";
    int *data = suffix_shift(template);
    for (size_t i = 0; i < strlen(template); i++)
    {
        printf("%d ", data[i]);
    }
    return EXIT_SUCCESS;
}