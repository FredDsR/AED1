#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Key;

typedef struct {
    Key key;
} Registry;

typedef struct Node * Pointer;

typedef struct Node {
    Registry reg;
    Pointer left, rigth;
} Node;


/*
    Esse search não faz sentido, se eu já tenho o registro pq vou buscar ele mesmo?
    Só se for pra pegar os dados que estão na árvore, mas aí não vale retornar um registro?
*/
void search(Registry *reg, Pointer pointer){
    if (!pointer) {
        printf("\nError: Registry not found.\n");
        return;
    }

    if (reg->key < pointer->reg.key) {
        search(reg, pointer->left);
        return;
    }

    if (reg->key > pointer->reg.key) {
        search(reg, pointer->rigth);
        return;
    }
    
    *reg = pointer->reg;
}

void insert(Registry reg, Pointer *pointer) {
    if (!*pointer) {
        *pointer = (Pointer) malloc(sizeof(Node));
        (*pointer)->reg = reg;
        (*pointer)->left = NULL;
        (*pointer)->rigth = NULL;
        return;
    }

    if (reg.key < (*pointer)->reg.key) {
        insert(reg, &(*pointer)->left);
        return;
    }

    if (reg.key > (*pointer)->reg.key) {
        insert(reg, &(*pointer)->rigth);
        return;
    }

    printf("\nError: Registry %d already exists.\n", reg.key);
}

void print_tree(Pointer *pointer) {
    if (*pointer){
        printf("(%d", (*pointer)->reg.key);
        print_tree(&(*pointer)->left);
        print_tree(&(*pointer)->rigth);
        printf(")");
    }
}

int main(int argc, char const *argv[])
{
    Pointer tree = NULL;
    Pointer to_search = NULL;
    Registry reg[10];

    time_t t;
    srand((unsigned) time(&t));
    

    for (int i = 0; i < 10; i++) {
        reg[i].key = rand() % 50;
        insert(reg[i], &tree);
    }

    printf("\nTree: ");
    print_tree(&tree);
    printf("\n");

    search(&reg[0], tree);

    printf("\nSub-Tree: ");
    print_tree(&to_search);
    printf("\n");
    

    return 0;
}
