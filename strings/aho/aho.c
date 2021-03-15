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

    return text;
}

node *init_node(char *parent, char s, bool terminate)
{
    node *n = malloc(sizeof(node));
    if (!n) {
        return n;
    }

    memset(n->childs, 0, sizeof(struct node *) * MAX_CHILDS);
    n->is_terminate = terminate;
    n->preffix = build_preffix(parent, s);
    return n;
}

void add_preffix(node *n, char *s, size_t size, size_t added)
{
    if (!n->childs[s[added]]) {
        n->childs[s[added]] = init_node(n->preffix, s[added], added == size)0;
    }

    if (added != size) {
        add_preffix(n->childs[s[added]], s, size, added+1);
    }
}

int main()
{
    char *text1 = "ABABC";

    node *n = init_node(NULL, '\0', false);
    add_preffix(n, text1, strlen(text1)-1, 0);
    n->preffix = "root";

    char *text2 = "AFOBAS";
    add_preffix(n, text2, strlen(text2)-1, 0);
    print_nodes(n);
}