#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Key;

typedef struct {
    Key key;
    int num;
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

void complex_deletion(Pointer to_remove, Pointer *to_replace){
    Pointer aux;

    if ((*to_replace)->rigth) {
        complex_deletion(to_remove, &(*to_replace)->rigth);
        return;
    }

    to_remove->reg = (*to_replace)->reg;
    aux = *to_replace;
    *to_replace = (*to_replace)->left;
    free(aux);
}

void delete(Registry reg, Pointer *pointer) {

    Pointer aux;

    if (!*pointer) {
        printf("Error: Registry %d not found.", reg.key);
        return;
    }

    if (reg.key < (*pointer)->reg.key){
        delete(reg, &(*pointer)->left);
        return;
    }

    if (reg.key > (*pointer)->reg.key) {
        delete(reg, &(*pointer)->rigth);
        return;
    }

    if (!(*pointer)->rigth) {
        aux = *pointer;
        *pointer = (*pointer)->left;
        free(aux);
        return;
    }

    if (!(*pointer)->left) {
        aux = *pointer;
        *pointer = (*pointer)->rigth;
        free(aux);
        return;
    }

    complex_deletion(*pointer, &(*pointer)->left);
}

void print_tree(Pointer *pointer) {
    if (*pointer){
        printf("(%d", (*pointer)->reg.key);
        print_tree(&(*pointer)->left);
        print_tree(&(*pointer)->rigth);
        printf(")");
    }
}

void initialize(Pointer *dictionary){
    *dictionary = NULL;
}

int main(int argc, char const *argv[])
{
    Pointer *tree = (Pointer *) malloc(sizeof(Pointer));
    Registry reg[10];
    Registry *reg_to_search = (Registry *) malloc(sizeof(Registry));

    time_t t;
    srand((unsigned) time(&t));
    
    initialize(tree);

    for (int i = 0; i < 10; i++) {
        reg[i].key = rand() % 50;
        reg[i].num = rand() % 50;
        insert(reg[i], tree);
    }

    printf("\n1 Tree: ");
    print_tree(tree);
    printf("\n");

    delete(reg[4], tree);
    
    printf("\n2 Tree: ");
    print_tree(tree);
    printf("\n");


    reg_to_search->key = reg[3].key;
    search(reg_to_search, *tree);

    printf("\n-> reg[3].num: %d\n", reg[3].num);
    printf("\n-> reg_to_search->num: %d\n", reg_to_search->num);

    return 0;
}
