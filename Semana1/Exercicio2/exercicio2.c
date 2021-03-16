#include <stdio.h>
#include <string.h>

void add_name(char *data_base, char *name_to_add){

    int base_length = 0;
    
    strcat(data_base, name_to_add);

    base_length = strlen(data_base);

    data_base[base_length] = ';';
}


void remove_name(char *data_base, char *name_to_remove) {

    char name_to_comp[21] = "";
    char aux_data_base[200] = "";
    int base_length = strlen(data_base);
    int aux_length = 0;
    int name_i = 0;
    int base_i = 0;

    for (base_i = 0; base_i < base_length; base_i++){
        
        if (data_base[base_i] == ';'){
            if (strcmp(name_to_remove, name_to_comp) == 0){
                name_i = 0;
                continue;
            } else {
                add_name(aux_data_base, name_to_comp);
                name_i = 0;
                continue;
            }
        }

        if (name_i < 20) {
            name_to_comp[name_i] = data_base[base_i];
            name_i += 1;
            name_to_comp[name_i] = '\0';
        }
    }

    strcpy(data_base, aux_data_base);
    aux_length = strlen(aux_data_base);

    data_base[aux_length] = '\0';
}

void list_names(char *data_base){
    int base_length = strlen(data_base);
    int i = 0;

    printf("\nNomes disponíveis:\n\n");
    for (i = 0; i < base_length; i++){
       
        if (data_base[i] == ';') {
            printf("\n");
            continue;
        }

        printf("%c", data_base[i]);
    }

}

void menu(char data_base[]){

    int op;
    char name[20];

    while (op != 4){

        printf("\n----------MENU----------\n");
        printf("  1) Adicionar nome\n");
        printf("  2) Remover nome\n");
        printf("  3) Listar\n");
        printf("  4) Sair\n");
        printf("------------------------\n");
        printf("Escolha uma opção acima e digite o numero respectivo: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("\nDigite o nome a ser adicionado: ");
            scanf("%s^\n", name);
            add_name(data_base, name);
            break;
        
        case 2:
            printf("\nDigite o nome a ser removido: ");
            scanf("%s^\n", name);
            remove_name(data_base, name);
            break;

        case 3:
            list_names(data_base);
            break;
        
        case 4:
            printf("\n -> Até logo! <-\n");
            break;

        default:
            printf("\n -> Digite uma opção válida! <-\n");
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    char data_base[200] = "";

    menu(data_base);

    return 0;
}
