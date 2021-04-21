#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_SORT 1
#define AGE_SORT 2
#define PHONE_SORT 3
typedef int SORT;


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
    SORT sort;
    Node *firstNode;
} List;

int compare_people(SORT sort, Person person_1, Person person_2){
    if (sort == NAME_SORT){
        return strcmp(person_1.name, person_2.name);
    } else if (sort == AGE_SORT) {
        if (person_1.age > person_2.age){
            return 1;
        } else if (person_1.age < person_2.age) {
            return -1;
        } else {
            return 0;
        }
    } else if (sort == PHONE_SORT) {
        if (person_1.phone > person_2.phone){
            return 1;
        } else if (person_1.phone < person_2.phone) {
            return -1;
        } else {
            return 0;
        }
    }

    return 0;
}

int search_by_name(List *list, char *name){
    int count = 0;
    Node *curr_node = list->firstNode;
    
    if (strcmp(list->firstNode->person.name, name) == 0){return 0;}
    
    while (curr_node->next ){
        curr_node = curr_node->next;
        count++;
        if (strcmp(curr_node->person.name, name) == 0){return count;}
    }
    return -1;
}

Node *createNode(Person person){
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node){printf("Error! Memory fault.");return NULL;}

    node->next = NULL;
    node->prev = NULL;
    node->person = person;

    return node;
    
}

Node *POP(List *list, unsigned int index){ 
    int count = 0;
    Node *cur_node = list->firstNode;

    if (list->length > 0) {
        if (index >= list->length) {
            printf("Sorry! Index is out of bounds 0 and %d.", list->length);
        } else if (index == 0) {
            list->firstNode = cur_node->next;
            list->length -= 1;
        } else {
            while (cur_node->next && count < index) {
                cur_node = cur_node->next;
            }
            
            cur_node->prev->next = cur_node->next;
            if (cur_node->next){
                cur_node->next->prev = cur_node->prev;
            }
            list->length -= 1;
        }
    }
    return cur_node;
}

void PUSH(List *list, Node *new_node){
    Node *curr_node = list->firstNode;

    if (list->length == 0) {
        
        list->firstNode = new_node;
        list->length += 1;

    } else {

        while (curr_node->next && compare_people(list->sort, curr_node->person, new_node->person) <= 0){
            curr_node = curr_node->next;
        }
        
        if (curr_node == list->firstNode) {
            
            if (compare_people(list->sort, curr_node->person, new_node->person) > 0){
                list->firstNode->prev = new_node;
                new_node->next = list->firstNode;
                list->firstNode = new_node;                
            } else {
                new_node->prev = curr_node;
                new_node->next = curr_node->next;
                curr_node->next = new_node;
            
                if (new_node->next){new_node->next->prev = new_node;}
            }

            list->length += 1;

        } else if (!curr_node->next){
            if (compare_people(list->sort, curr_node->person, new_node->person) > 0){
                
                new_node->prev = curr_node->prev;
                curr_node->prev = new_node;
                new_node->next = curr_node;

                if(new_node->prev){new_node->prev->next = new_node;}

            } else {
                new_node->prev = curr_node;
                new_node->next = curr_node->next;
                curr_node->next = new_node;
            
                if (new_node->next){new_node->next->prev = new_node;}
            }

            list->length += 1;
        } else {
            new_node->next = curr_node;
            new_node->prev = curr_node->prev;
            curr_node->prev = new_node;
            
            if (new_node->prev){new_node->prev->next = new_node;}

            list->length += 1;
        }
    }
}

void add_person(List *list){
    Person new_person;

    printf("\nEnter the new contact info:\n");
    printf(" Name: ");
    scanf("%s^\n", new_person.name);
    printf(" Phone: ");
    scanf("%d", &new_person.phone);
    printf(" Age: ");
    scanf("%d", &new_person.age);

    PUSH(list, createNode(new_person));
}

void remove_person(List *list) {
    char name_to_remove[10];
    int index = 0;
    Node *node;

    if (list->length == 0){
        printf("Your contact list is empty.\n");
    } else {
        
        printf("\nEnter the contact name to be removed: ");
        scanf("%s^\n", name_to_remove);
        
        index = search_by_name(list, name_to_remove);

        if (index < 0) {
            printf("Sorry, the contact named %s do not exists.\n", name_to_remove);
        } else {
            node = POP(list, index);

            free(node);
        }
    }
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
            printf("| |_ Age: %d years old\n", cur_node->person.age);
            cur_node = cur_node->next;
        }
        printf("|\n");
        printf("|_ End.\n");
    }
}

void find_person(List *list) {
    char name_to_remove[10];
    int index;
    Node *node;

    if (list->length == 0){
        printf("Your contact list is empty.\n");
    } else {
        
        printf("\nEnter the contact name to be searched: ");
        scanf("%s^\n", name_to_remove);
        
        index = search_by_name(list, name_to_remove);

        if (index < 0) {
            printf("Sorry, the contact named %s do not exists.\n", name_to_remove);
        } else {
            node = POP(list, index);

            printf("Contact Info:\n");
            printf("|_Name: %s\n", node->person.name);
            printf("|_Age: %d years old\n", node->person.age);
            printf("|_Phone: %d\n", node->person.phone);
            printf("|_Index: %d\n", index);

            PUSH(list, node);
        }
    }
}

void reset_list(List *list){
    while (list->length > 0) {
        free(POP(list, list->length - 1));
    }   
}

int main(int argc, char const *argv[]) {

    void *pBuffer = malloc(sizeof(List) + sizeof(unsigned long) + sizeof(int));
    /*  
    Primira posição é um ponteiro para a lista - ((List *)pBuffer)
    Segunda posição é um inteiro representando o tamanho total alocado - *((unsigned long *)(pBuffer + sizeof(List)))
    Terceira posição é um inteiro para controlar o switch - pBuffer + sizeof(List) + sizeof(int)
    */

    if(!pBuffer){printf("Error! Memory fault"); return -1;}

    // Tamanho atual alocado pro pBuffer
    *((unsigned long *)(pBuffer + sizeof(List))) = sizeof(List) + sizeof(unsigned long) + sizeof(int);

    // Parametros iniciais da lista
    ((List *)pBuffer)->length = 0;
    ((List *)pBuffer)->firstNode = NULL;

    // Controlador do switch
    *((int *)(pBuffer + sizeof(List) + sizeof(unsigned long))) = -1;


    printf("\n-----------------Available sortings-----------------\n");
    printf(" (%d) Sort by name\n", NAME_SORT);
    printf(" (%d) Sort by age\n", AGE_SORT);
    printf(" (%d) Sort by phone\n", PHONE_SORT);
    printf("Enter the respective number of the desired ordering: ");
    scanf("%d", &((List *)pBuffer)->sort);

    while (*((int *)(pBuffer + sizeof(List) + sizeof(unsigned long))) != 0){

        printf("\n----------CONTACTS----------\n");
        printf("  1) Add contact\n");
        printf("  2) Remove contact\n");
        printf("  3) Search by name\n");
        printf("  4) List\n");
        printf("  0) Exit\n");
        printf("------------------------------\n");
        printf("Choice an option above and type the respective number: ");
        scanf("%d", ((int *)(pBuffer + sizeof(List) + sizeof(unsigned long))));

        switch (*((int *)(pBuffer + sizeof(List) + sizeof(unsigned long)))) {
        case 1:
            add_person(((List *)pBuffer));
            break;
        
        case 2:
            remove_person(((List *)pBuffer));
            break;
        
        case 3:
            find_person(((List *)pBuffer));
            break;

        case 4:
            list_people(((List *)pBuffer));
            break;
        
        case 0:
            reset_list(((List *)pBuffer));
            printf("\nBye!\n");
            break;

        default:
            printf("\n -> Type a valid option! <-\n");
            break;
        }
    }
    free(pBuffer);
    return 0;
}
