#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    int age;
    int phone;
} Person;

typedef struct _node{
    Person person;
    struct _node *next;
    struct _node *prev;
} Node;

typedef struct {
    int length;
    Node *firstNode;
} List;


Node *createNode(Person person){
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node){printf("Error! Memory fault.");return NULL;}

    node->next = NULL;
    node->prev = NULL;
    node->person = person;

    return node;
    
}

int search_by_name(List *list, char *name){
    int count = 0;
    Node *cur_node = list->firstNode;
    while (cur_node->next && strcmp(name, cur_node->person.name) != 0){cur_node = cur_node->next;count++;}
    return count;
}

//TODO ta dando falha de segmentação aqui -> testar remover um nome
Node *POP(List *list, unsigned int index){ 
    int count = 0;
    Node *cur_node = list->firstNode;

    if (index > list->length - 1) {
        printf("Sorry! Index is out of bounds 0 and %d.", list->length);
    } else if (index == 0) {
        list->firstNode = cur_node->next;
        list->length -= 1;
    } else {
        while (cur_node->next && count < index) {
            cur_node = cur_node->next;
        }
        
        cur_node->prev->next = cur_node->next;
        cur_node->next->prev = cur_node->prev;

        list->length -= 1;
    }
    return cur_node;
}

void PUSH(List *list, Node *new_node, unsigned int index){
    int count = 0;
    Node *curr_node = list->firstNode;

    if (list->length < index) { 
    
        printf("Sorry! The index is out of bounds 0 and %d", list->length);
    
    } else if (list->length == 0) {
        
        list->firstNode = new_node;
        list->length += 1;
    
    } else if (index == 0) {
        
        list->firstNode->prev = new_node;
        new_node->next = list->firstNode;
        list->firstNode = new_node;

        list->length += 1;

    } else {

        while (curr_node->next && count < index){
            curr_node = curr_node->next;
            count++;
        }

        new_node->prev = curr_node;
        new_node->next = curr_node->next;
        curr_node->next = new_node;
        
        list->length += 1;
    }
}

void add_person(List *list){
    int index = 0;
    Person new_person;

    printf("\nEnter the new contact info:\n");
    printf(" Name: ");
    scanf("%s^\n", new_person.name);
    printf(" Phone: ");
    scanf("%d", &new_person.phone);
    printf(" Age: ");
    scanf("%d", &new_person.age);
    printf("Where do you want to add this contact? 0 - %d: ", list->length);
    scanf("%d", &index);

    PUSH(list, createNode(new_person), index);
}

void remove_person(List *list) {
    char name_to_remove[10];
    int index = 0;
    Node *node;

    printf("\nEnter the contact name to be removed: ");
    scanf("%s^\n", name_to_remove);

    index = search_by_name(list, name_to_remove);

    node = POP(list, index);

    free(node);
}

void list_people(List *list) {
    Node *cur_node;
    cur_node = list->firstNode;

    if (list->length == 0) {
        printf(" Sorry, your contact list is empty. :(\n");
    } else {
        printf("\n\nYour contact list:\n");
        while (cur_node) {
            printf("|\n");
            printf("|_ %s\n", cur_node->person.name);
            printf("| |_ Phone: %d\n", cur_node->person.phone);
            printf("| |_ Age: %d\n", cur_node->person.age);
            cur_node = cur_node->next;
        }
        printf("|\n");
        printf("|_ End.\n");
    }
}

int main(int argc, char const *argv[]) {

    int op = -1;
    
    List *peopleList = malloc(sizeof(List));
    if (!peopleList){printf("Error! Memory fault.");return -1;}

    peopleList->length = 0;
    peopleList->firstNode = NULL;

    while (op != 0){

        printf("\n----------CONTACTS----------\n");
        printf("  1) Add contact\n");
        printf("  2) Remove contact\n");
        printf("  3) Search by name\n");
        printf("  4) List\n");
        printf("  0) Exit\n");
        printf("------------------------------\n");
        printf("Choice an option above and type the respective number: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            add_person(peopleList);
            break;
        
        case 2:
            remove_person(peopleList);
            break;
        
        case 3:
            // find_person(peopleList);
            break;

        case 4:
            list_people(peopleList);
            break;
        
        case 0:
            // peopleList = reset_list(peopleList);
            printf("\nBye!\n");
            break;

        default:
            printf("\n -> Type a valid option! <-\n");
            break;
        }
    }
    
    free(peopleList);

    return 0;
}
