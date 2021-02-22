#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CHILDS 256 // alphabet

typedef struct node
{
    bool is_root;
    bool is_terminate;

    char *preffix;
    struct node *childs[MAX_CHILDS];
    struct node *term_ref;
    struct node *suffix_ref;
}node;

char *build_preffix(char *parent, char s)
{
    size_t len = (parent == NULL) ? 0 : strlen(parent);
    char *text = malloc(sizeof(char)*(len+1));
    if (!text) {
        return NULL;
    }

    if (len != 0) {
        strcpy(text, parent);
    }

    text[len] = s;
    text[len+1] = '\0';

    printf("%s\n", text);
    return text;
}

node *init_node(char *parent, char s)
{
    node *n = malloc(sizeof(node));
    if (!n) {
        return n;
    }

    n->is_terminate = false;
    n->preffix = build_preffix(parent, s);
    return n;
}

void add_suffix(node *n, char s)
{
    if (!n->childs[s]) {
        n->childs[s] = init_node(n->preffix, s);
        return;
    } 

    add_suffix(n->childs[s], s);
}

int main()
{
    node n;
    char *text = "ABCDEDFDAVDSDA";
    for (size_t i = 0; i < strlen(text); i++)
    {
        add_suffix(&n, text[i]);
    }
}