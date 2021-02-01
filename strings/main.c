#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "alphabet.h"

int boyer_moore(const char *str, const char *template)
{
    size_t str_len = strlen(str);
    size_t template_len = strlen(template);
    if (template_len == 0 || template_len > str_len) return -1;

    init_alphabet_shift(template, template_len);

    size_t begin = 0;
    while (begin + template_len -1 < str_len)
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
        
        begin += get_shift(str[begin]);
    }
    
    return -1;
}

int main()
{
    printf("%d\n", boyer_moore("kololkol", "kol"));
    return EXIT_SUCCESS;
}