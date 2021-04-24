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
    struct _node *my_address;
} Node;

typedef struct {
    int length;
    SORT sort;
    Node *firstNode;
} List;

int compare_people(void *pBuffer){
    // Quarta posição é o nodo que ta sendo inserido *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))
    // Quinta posição é o nodo corrente *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
    
    if (((List *)pBuffer)->sort == NAME_SORT){
        return strcmp(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.name, ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->person.name);
    } else if (((List *)pBuffer)->sort == AGE_SORT) {
        if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.age > ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->person.age){
            return 1;
        } else if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.age < ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->person.age) {
            return -1;
        } else {
            return 0;
        }
    } else if (((List *)pBuffer)->sort == PHONE_SORT) {
        if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.phone > ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->person.phone){
            return 1;
        } else if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.phone < ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->person.phone) {
            return -1;
        } else {
            return 0;
        }
    }

    return 0;
}

void *search_by_name(void *pBuffer){

    // Quarta posição é o indice a ser deletado         *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10)) - sizeof(Node))
    // Quinta posição é o nome da pessoa a ser deletada *((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)) - sizeof(Node))
    // Sexta posição é o nodo corrente                  *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10) - sizeof(Node))) = 0;

    if (strcmp(((List *)pBuffer)->firstNode->person.name, ((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)) - sizeof(Node))) == 0){
        // Quarta posição é o indice a ser deletado         *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10)))
        // Quinta posição é o nome da pessoa a ser deletada *((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)))
        *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
        pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
        if (!pBuffer){printf("Error! Memory fault.");return NULL;}
        
        *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10))) = 0;
        
        return pBuffer;
    }

    *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))) = *(((List *)pBuffer)->firstNode);

    while (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next){
        *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))) = *(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next);
        *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10) - sizeof(Node))) += 1;
        if (strcmp(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.name, ((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)) - sizeof(Node))) == 0){
            // Quarta posição é o indice a ser deletado         *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10)))
            // Quinta posição é o nome da pessoa a ser deletada *((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)))
            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}
            
            return pBuffer;
        }
    }

    // Quarta posição é o indice a ser deletado         *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10)))
    // Quinta posição é o nome da pessoa a ser deletada *((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}
    *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10))) = -1;

    return pBuffer;
}

Node *POP(void *pBuffer){ 

    // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(int) * 2) - sizeof(Node)))
    // Quinta posição é o nodo corrente         *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))
    // Sexta posição é o contador               *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(int) + sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int))) = 0;
    *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int))) = *(((List *)pBuffer)->firstNode);

    if (((List *)pBuffer)->length > 0) {
        if (*((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(int) * 2) - sizeof(Node))) >= ((List *)pBuffer)->length) {
            printf("Sorry! Index is out of bounds 0 and %d.", ((List *)pBuffer)->length);
        } else if (*((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(int) * 2) - sizeof(Node))) == 0) {
            ((List *)pBuffer)->firstNode = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->next;
            if(((List *)pBuffer)->firstNode){((List *)pBuffer)->firstNode->prev = NULL;}
            ((List *)pBuffer)->length -= 1;
        } else {
            while (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->next && *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int))) < *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(int) * 2) - sizeof(Node)))) {
                *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int))) = *(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->next);
                *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int))) += 1;
            }
            
            ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->my_address->prev->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->my_address->next;
            if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->my_address->next){
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->my_address->next->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(int)))->my_address->prev;
            }
            ((List *)pBuffer)->length -= 1;
        }
    }

    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}
    return pBuffer;
}

Node *createNode(void *pBuffer){
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (!new_node){printf("Error! Memory fault.");return NULL;}

    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->my_address = new_node;
    new_node->person = *(Person *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Person));

    return new_node;
}

void *PUSH(void *pBuffer){
    
    // Quarta posição é o nodo que ta sendo inserido *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))
    // Quinta posição é o nodo corrente *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}


    if (((List *)pBuffer)->length == 0) {
        
        ((List *)pBuffer)->firstNode = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;
        ((List *)pBuffer)->length += 1;

    } else {

        *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))) = *(((List *)pBuffer)->firstNode);
        
        while (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next && compare_people(pBuffer) <= 0){
            *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))) = *(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next);
        }
        
        if (((List *)pBuffer)->firstNode == ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address) {
            
            if (compare_people(pBuffer) > 0){
                ((List *)pBuffer)->firstNode->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next = ((List *)pBuffer)->firstNode;
                ((List *)pBuffer)->firstNode = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;                
            } else {
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;
            
                if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next){((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;}
            }

            ((List *)pBuffer)->length += 1;

        } else if (!((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next){
            if (compare_people(pBuffer) > 0){
                
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->prev;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address;

                if(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev){((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;}

            } else {
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next;
                ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;
            
                if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next){((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;}
            }

            ((List *)pBuffer)->length += 1;
        } else {
            ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address;
            ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->prev;
            ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address->prev = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;
            
            if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev){((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address->prev->next = ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(Node) * 2)))->my_address;}

            ((List *)pBuffer)->length += 1;
        }
    }

    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    return pBuffer;
}

void *add_person(void *pBuffer){
    
    // Quarta posição é o nodo que ta sendo inserido *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(Person)))
    // Quinta posição é a pessoa que ta sendo inserida *((Person *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Person)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(Node) + sizeof(Person);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    printf("\nEnter the new contact info:\n");
    printf(" Name: ");
    scanf("%s^\n", ((Person *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List)))  - sizeof(Person)))->name);
    printf(" Phone: ");
    scanf("%d", &((Person *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List)))  - sizeof(Person)))->phone);
    printf(" Age: ");
    scanf("%d", &((Person *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Person)))->age);


    *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node) - sizeof(Person))) = *createNode(pBuffer);

    // Quarta posição é o nodo que ta sendo inserido *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Person);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    pBuffer = PUSH(pBuffer);

    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    return pBuffer;
}

void *remove_person(void *pBuffer) {

    if (((List *)pBuffer)->length == 0){
        printf("Your contact list is empty.\n");
    } else {

        // Quarta posição é o indice a ser deletado         *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10)))
        // Quinta posição é o nome da pessoa a ser deletada *((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)))
        *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(int) + (sizeof(char)*10);
        pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
        if (!pBuffer){printf("Error! Memory fault.");return NULL;}

        printf("\nEnter the contact name to be removed: ");
        scanf("%s^\n", ((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10))));
        
        pBuffer = search_by_name(pBuffer);

        if (*((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10))) < 0) {
            printf("Sorry, the contact named %s do not exists.\n", ((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10))));
        
            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}
        } else {

            // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int)))
            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}

            // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - sizeof(Node)))
            // Quinta posição é o nodo a ser deletado   *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
            pBuffer = POP(pBuffer);
            
            free(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address);

            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - sizeof(Node);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}
        }
    }

    return pBuffer;
}

void *list_people(void *pBuffer) {


    // Quarta posição é o nodo corrente *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    if (((List *)pBuffer)->length == 0) {
        printf(" Sorry, your contact list is empty. :(\n");
    } else {
        *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))) = *(((List *)pBuffer)->firstNode);

        printf("\n\nYour contact list:\n");
        while (1) {
            printf("|\n");
            printf("|_ %s\n", ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.name);
            printf("| |_ Phone: %d\n", ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.phone);
            printf("| |_ Age: %d years old\n", ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.age);

            if (((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next){
                *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node))) = *(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->next);
            } else {
                break;
            }
        }
        printf("|\n");
        printf("|_ End.\n");
    }

    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    return pBuffer;
}

void *find_person(void *pBuffer) {

    if (((List *)pBuffer)->length == 0){
        printf("Your contact list is empty.\n");
    } else {
        // Quarta posição é o indice a ser deletado         *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10)))
        // Quinta posição é o nome da pessoa a ser deletada *((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10)))
        *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(int) + (sizeof(char)*10);
        pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
        if (!pBuffer){printf("Error! Memory fault.");return NULL;}

        printf("\nEnter the contact name to be searched: ");
        scanf("%s^\n", ((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10))));
        
        pBuffer = search_by_name(pBuffer);

        if (*((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10))) < 0) {
            printf("Sorry, the contact named %s do not exists.\n", ((char *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10))));

            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}
        } else {
            // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int)))
            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - (sizeof(char)*10);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}

            // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - sizeof(Node)))
            // Quinta posição é o nodo a ser deletado   *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
            pBuffer = POP(pBuffer);

            printf("Contact Info:\n");
            printf("|_Name: %s\n", ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.name);
            printf("|_Age: %d years old\n", ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.age);
            printf("|_Phone: %d\n", ((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->person.phone);
            printf("|_Index: %d\n", *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - (sizeof(char)*10))));

            pBuffer = PUSH(pBuffer);

            *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - sizeof(Node);
            pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
            if (!pBuffer){printf("Error! Memory fault.");return NULL;}
        }
    }
    return pBuffer;
}

void *reset_list(void *pBuffer){

    // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int)))
    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) + sizeof(int);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    while (((List *)pBuffer)->length > 0) {
        *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int))) = ((List *)pBuffer)->length - 1;
        
        // Quarta posição é o indice a ser deletado *((int *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int) - sizeof(Node)))
        // Quinta posição é o nodo a ser deletado   *((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))
        pBuffer = POP(pBuffer);
        
        free(((Node *)(pBuffer + *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node)))->my_address);

        *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(Node);
        pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
        if (!pBuffer){printf("Error! Memory fault.");return NULL;}
    }   

    *((unsigned long *)(pBuffer + sizeof(List))) = *((unsigned long *)(pBuffer + sizeof(List))) - sizeof(int);
    pBuffer = realloc(pBuffer, *((unsigned long *)(pBuffer + sizeof(List))));
    if (!pBuffer){printf("Error! Memory fault.");return NULL;}

    return pBuffer;
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
        printf("\n\n-> Tamanho do buffer: %lu", *((unsigned long *)(pBuffer + sizeof(List))));
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
            pBuffer = add_person(pBuffer);
            break;
        
        case 2:
            pBuffer = remove_person(pBuffer);
            break;
        
        case 3:
            pBuffer = find_person(((List *)pBuffer));
            break;

        case 4:
            pBuffer = list_people(pBuffer);
            break;
        
        case 0:
            pBuffer = reset_list(pBuffer);
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
