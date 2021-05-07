#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef int Key;

typedef struct {
    Key key;
} Registry;

typedef struct Node * Pointer;

typedef struct Node {
    Registry reg;
    Pointer left, right;
} Node;

int count_nodes(Pointer pointer){
    if (!pointer) {
        return 0;
    }

    return 1 + count_nodes(pointer->left) + count_nodes(pointer->right);
}

int height(Pointer pointer){
    int left_height = 0, right_height = 0;
    if (!pointer){
        return 0;
    }
    left_height = height(pointer->left);
    right_height = height(pointer->right);
    
    if (left_height > right_height) {
        return 1 + left_height;
    } else {
        return 1 + right_height;
    }
}

int get_balancing_factor(Pointer *pointer){
    return height((*pointer)->left) - height((*pointer)->right);
}

void rotate_left(Pointer *pointer_to_root){
    Pointer aux;
    aux = (*pointer_to_root)->right;
    (*pointer_to_root)->right = aux->left;
    aux->left = (*pointer_to_root);
    (*pointer_to_root) = aux;   
}

void rotate_right(Pointer *pointer_to_root){
    Pointer aux;
    aux = (*pointer_to_root)->left;
    (*pointer_to_root)->left = aux->right;
    aux->right = (*pointer_to_root);
    (*pointer_to_root) = aux;
}

int balance_left(Pointer *pointer){
    int left_bf = get_balancing_factor(&(*pointer)->left);

    if (left_bf > 0) {
        rotate_right(pointer);
        return 1;
    } else if (left_bf < 0) {
        rotate_left(&((*pointer)->left));
        rotate_right(pointer);
        return 1;
    }
    return 0;
}

int balance_right(Pointer *pointer){
    int right_bf = get_balancing_factor(&(*pointer)->right);

    if (right_bf < 0) {
        rotate_left(pointer);
        return 1;
    } else if (right_bf > 0) {
        rotate_right(&((*pointer)->right));
        rotate_left(pointer);
        return 1;
    }
    return 0;
}

int balance(Pointer *pointer){
    int root_bf = get_balancing_factor(pointer);
    if (root_bf > 1) {
        return balance_left(pointer);
    }
    if (root_bf < -1) {
        return balance_right(pointer);
    }
    return 0;
}

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
        search(reg, pointer->right);
        return;
    }
    
    *reg = pointer->reg;
}

int insert(Registry reg, Pointer *pointer) {
    if (!*pointer) {
        *pointer = (Pointer) malloc(sizeof(Node));
        (*pointer)->reg = reg;
        (*pointer)->left = NULL;
        (*pointer)->right = NULL;
        return 1;
    }

    if (reg.key < (*pointer)->reg.key) {
        if (insert(reg, &(*pointer)->left)){
            if (balance(pointer)){
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }

    if (reg.key > (*pointer)->reg.key) {
        if (insert(reg, &(*pointer)->right)) {
            if (balance(pointer)){
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }

    printf("\nError: Registry %d already exists.\n", reg.key);
    return 0;
}

void complex_deletion(Pointer to_remove, Pointer *to_replace){
    Pointer aux;

    if ((*to_replace)->right) {
        complex_deletion(to_remove, &(*to_replace)->right);
        return;
    }

    to_remove->reg = (*to_replace)->reg;
    aux = *to_replace;
    *to_replace = (*to_replace)->left;
    free(aux);
}

int delete(Registry reg, Pointer *pointer) {
    Pointer aux;

    if (!*pointer) {
        printf("Error: Registry %d not found.", reg.key);
        return 0;
    }

    if (reg.key < (*pointer)->reg.key){
        if (delete(reg, &(*pointer)->left)){
            balance(pointer);
            return 1;
        } else {
            return 0;
        }
    }

    if (reg.key > (*pointer)->reg.key) {
        if (delete(reg, &(*pointer)->right)){
            balance(pointer);
            return 1;
        } else {
            return 0;
        }
    }

    if (!(*pointer)->right) {
        aux = *pointer;
        *pointer = (*pointer)->left;
        free(aux);
        return 1;
    }

    if (!(*pointer)->left) {
        aux = *pointer;
        *pointer = (*pointer)->right;
        free(aux);
        return 1;
    }

    complex_deletion(*pointer, &(*pointer)->left);
    return 1;
}

void print_tree(Pointer *pointer) {
    if (*pointer){
        printf("(%d", (*pointer)->reg.key);
        print_tree(&(*pointer)->left);
        print_tree(&(*pointer)->right);
        printf(")");
    }
}

void initialize(Pointer *dictionary){
    *dictionary = NULL;
}

int standard_avl_verification(Pointer pointer){
    int bf = 0;

    if (!pointer) {
        return 1;
    }

    if (!standard_avl_verification(pointer->left)){return 0;}
    if (!standard_avl_verification(pointer->right)){return 0;}

    bf = get_balancing_factor(&pointer);
    
    if ((bf > 1) || (bf < -1)){
        return 0;
    } else {
        return 1;
    }
}

int calc_avl_verification(int nodes_qty, int tree_height){
    if (((1.44 * log2f((float) nodes_qty + 2)) + 1.0) > (float) tree_height){
        return 1;
    } else {
        return 0;
    }
}

void print_tree_status(Pointer *tree){
    printf("\nTree: ");
    print_tree(tree);
    printf("\n-> Standard AVL Verification:\t%d", standard_avl_verification(*tree));
    printf("\n-> Calc AVL Verification:\t%d", calc_avl_verification(count_nodes(*tree), height(*tree)));
    printf("\nTrue = 1; False = 0\n");
}

int main(int argc, char const *argv[])
{
    int node_qty = 0, key_to_remove = 0;
    Registry reg;
    Pointer *tree = (Pointer *) malloc(sizeof(Pointer));
    srand((unsigned) time(0));
    
    initialize(tree);

    printf("Enter the number of desired nodes: ");
    scanf("%d", &node_qty);

    for (int i = 0; i < node_qty; i++) {
        reg.key = rand() % 50;
        insert(reg, tree);
    }

    print_tree_status(tree);

    for (int i = 0; i < count_nodes(*tree); i++){
        printf("Choose a key to remove: ");
        scanf("%d", &key_to_remove);
        reg.key = key_to_remove;
        delete(reg, tree);

        print_tree_status(tree);
    }

    return 0;
}
