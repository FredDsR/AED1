#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[30];
    int age;
    int height;
} Person;

Person read_person(){
    Person person;

    printf("Enter with the new person data.\n");
    printf("Name: ");
    scanf("%s^\n", person.name);
    printf("Age: ");
    scanf("%d", &person.age);
    printf("Height (cm): ");
    scanf("%d", &person.height);

    return person;
}

Person *add_person(Person *people, int *people_qty){
    int new_people_qty = *people_qty + 1;
    int new_people_index = *people_qty;
    
    if (*people_qty == 0) {
        people = (Person *) malloc(sizeof(Person));
    } else {
        people = (Person *) realloc(people, sizeof(Person) * new_people_qty);
    }

    people[new_people_index] = read_person();
    
    *people_qty = new_people_qty;
    return people;
}

void print_people(Person *people, int *people_qty){
    printf("List of people:\n");
    for (int i = 0; i < *people_qty; i++) {
        printf("|\n");
        printf("|_%s\n", people[i].name);
        printf("| |_%d years\n", people[i].age);
        printf("| |_%d cm\n", people[i].height);
    }
    printf("|\n");
    printf("|_End\n");  
}

int main(int argc, char const *argv[])
{
    char op;
    
    Person *people;
    int *people_qty = (int *) malloc(sizeof(int));

    if (!people_qty){printf("Error! Memory fault.");return -1;}

    *people_qty = 0;

    while (1) {
        printf("\n\n--------------------------\n");
        printf("Do you want add another person? y or n: ");
        scanf("%c", &op);

        if (op == 'y') {
            people = add_person(people, people_qty);
            if (!people){printf("Error! Memory fault.");return -1;}
            continue;}
        if (op == 'n') {break;}
    }

    print_people(people, people_qty);

    free(people);
    free(people_qty);

    return 0;
}

