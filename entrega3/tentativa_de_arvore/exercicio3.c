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

Tree * create_tree(){
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    
    tree->root = NULL;

    return tree;
}

Node * create_node(int value){
    Node *node = (Node *) malloc(sizeof(Node));

    node->left = NULL;
    node->rigth = NULL;
    node->value = value;

    return node;
}

Node * search(Node *root, int value_to_search){
    if (!root) {return NULL;}

    if (root->value == value_to_search) {return root;}

    if (value_to_search < root->value){return search(root->left, value_to_search);}

    if (value_to_search > root->value){return search(root->rigth, value_to_search);}

    return NULL;
}

Node *insert(Node *root, int value){
    Node *new_node = create_node(value);

    if (!root){
        return new_node;
    } else {
        if (root) {
            if (new_node->value <= root->value){
                if (root->left){
                    insert(root->left, value);
                    return root;
                } else {
                    root->left = new_node;
                    return root;
                }
            } else {
                if(root->rigth){
                    insert(root->rigth, value);
                    return root;
                } else {
                    root->rigth = new_node;
                    return root;
                }
            }
        }
    }
    return root;
}

void print_tree(Node *root){
    if(root){
        printf("(%d", root->value);
        print_tree(root->left);
        print_tree(root->rigth);
        printf(")");
    }
}

int main(int argc, char const *argv[]) {

    Tree *tree = create_tree();
    tree->root = insert(tree->root, 4);
    tree->root = insert(tree->root, 5);
    tree->root = insert(tree->root, 2);
    tree->root = insert(tree->root, 6);
    tree->root = insert(tree->root, 3);
    tree->root = insert(tree->root, 1);
    
    printf("\nÁrvore: ");
    print_tree(tree->root);
    printf("\n");
    
    printf("\nSub-árvore: ");
    print_tree(search(tree->root, 2));
    printf("\n");

    return 0;
}
