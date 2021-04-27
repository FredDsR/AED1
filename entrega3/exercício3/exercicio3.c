#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node *left;
    struct _node *rigth;
} Node;

typedef struct {
    Node *root;
} Tree;

int main(int argc, char const *argv[]) {
    return 0;
}
