#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    int age;
    int phone;
} Person;


int find_person_index(void *pBuffer, char *name_to_find) {
    int len = *(int *)pBuffer;

    Person person;

    for (int i = 0; i < len; i++) {
        person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * i));

        if (strcmp(person.name, name_to_find) == 0) {
            return i;
        }
    }

    return -1;
}


void find_person(void *pBuffer) {
    char name_to_find[10];
    int person_index = 0;
    Person person;

    printf("\nEnter the name to be searched: ");
    scanf("%s^\n", name_to_find);

    person_index = find_person_index(pBuffer, name_to_find);

    if (person_index == -1) {
        printf("\n -> The contact %s was not found! <-\n", name_to_find);
    } else {
        person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * person_index));

        printf("Contact found:\n");
        printf(" %s\n", person.name);
        printf(" |_ Phone: %d\n", person.phone);
        printf(" |_ Age: %d\n", person.age);
    }
}

void *add_person(char *pBuffer){
    
    int old_len = *(int *)pBuffer;
    int new_len = old_len + 1;
    
    Person new_person;

    printf("\nEnter the new contact info:\n");
    printf(" Name: ");
    scanf("%s^\n", new_person.name);
    printf(" Phone: ");
    scanf("%d", &new_person.phone);
    printf(" Age: ");
    scanf("%d", &new_person.age);

    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Person) * new_len));

    *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * old_len)) = new_person;
    
    *(int *)pBuffer = new_len;

    return pBuffer;
}

char *remove_person(char *pBuffer) {
    
    char name_to_remove[10];
    int person_index;
    int old_len = *(int *)pBuffer; 
    int new_len = old_len - 1;
    int count = 0;

    Person next_person;

    printf("\nEnter the contact name to be removed: ");
    scanf("%s^\n", name_to_remove);

    person_index = find_person_index(pBuffer, name_to_remove);

    count = person_index + 1;

    if (person_index == -1){
        printf("\n -> The contact %s was not found! <-\n", name_to_remove);
    } else {
        while (count < old_len){
            next_person = *((Person *)(pBuffer + sizeof(int) + (sizeof(Person) * count)));

            *((Person *)(pBuffer + sizeof(int) + (sizeof(Person) * (count - 1)))) = next_person;

            count++;
        }
        
        pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Person) * new_len));
    
        *(int *)pBuffer = new_len;
    }

    return pBuffer;
}

void list_people(char *pBuffer){
    int len = *(int *)pBuffer;

    Person person;

    if (len == 0) {
        printf("\nYour contact list are empty :(\n");
    } else {
        printf("\n\nYour contact list:\n");
        for (int i = 0; i < len; i++)
        {
            person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * i));
            
            printf("|\n");
            printf("|_ %s\n", person.name);
            printf("| |_ Phone: %d\n", person.phone);
            printf("| |_ Age: %d\n", person.age);
        }
        printf("|\n");
        printf("|_ End.\n");
    }
}

int main(int argc, char const *argv[])
{
    int op = -1;
    
    void *pBuffer = malloc(sizeof(int));
    if (!pBuffer){printf("Error! Memory fault.");return -1;}
    
    *(int *)pBuffer = 0;

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
            pBuffer = add_person(pBuffer);
            break;
        
        case 2:
            pBuffer = remove_person(pBuffer);
            break;
        
        case 3:
            find_person(pBuffer);
            break;

        case 4:
            list_people(pBuffer);
            break;
        
        case 0:
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
