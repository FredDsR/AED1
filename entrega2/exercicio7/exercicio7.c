#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[30];
    int age, height;
} Person;

Person people[10];

int main(int argc, char const *argv[])
{
    void *pBuffer = malloc(sizeof(char) + sizeof(int));
    if(!pBuffer){printf("\n-> Error! Memory fault. <-\n");return -1;}

    *(char *)pBuffer = 'y';
    *(int *)(pBuffer + sizeof(char)) = 0;
    while (*(int *)(pBuffer + sizeof(char)) < 10)
    {
        printf("\nDo you want add a new person? y or n: ");
        scanf("%c", (char *)pBuffer);

        if (*(char *)pBuffer == 'y')
        {
            printf("Enter with the new person data:\n");
            printf("Name: ");
            scanf("%s^\n", people[*(int *)(pBuffer + sizeof(char))].name);
            printf("Age: ");
            scanf("%d^\n", &people[*(int *)(pBuffer + sizeof(char))].age);
            printf("Height (cm): ");
            scanf("%d^\n", &people[*(int *)(pBuffer + sizeof(char))].height);
            getchar();
            *(int *)(pBuffer + sizeof(char)) += 1;
            continue;
        }

        if ((*(char *)pBuffer == 'n')){printf("\nBye!\n");break;}
        
        printf("\n-> Only 'y' or 'n', please! <-\n");
    }
    
    pBuffer = realloc(pBuffer, sizeof(char) + (sizeof(int) * 2));

    printf("\nList of people:\n");
    for (*(int *)(pBuffer + sizeof(char) + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(char) + sizeof(int)) < *(int *)(pBuffer + sizeof(char)); *(int *)(pBuffer + sizeof(char) + sizeof(int))+=1)
    {
        printf("|\n");
        printf("|_%s\n", people[*(int *)(pBuffer + sizeof(char) + sizeof(int))].name);
        printf("| |_%d years\n", people[*(int *)(pBuffer + sizeof(char) + sizeof(int))].age);
        printf("| |_%d cm\n", people[*(int *)(pBuffer + sizeof(char) + sizeof(int))].height);
    }
    printf("|\n");
    printf("|_End\n");
    
    free(pBuffer);

    return 0;
}
