#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *add_char_to_string(char *string, int *length, char char_to_add){

    string[*length-1] = char_to_add;

    *length += 1;

    string = (char *) realloc(string, sizeof(char) * (*length));

    string[*length - 1] = '\0';

    return string;
}

char *read_name(char *name, int *length){
    
    char letter = '\0';
    getchar();

    do {

        letter = getchar();
        if (letter != '\n'){name = add_char_to_string(name, length, letter);}

    } while (letter != '\n');

    return name;
}

int find_name(char *data_base, char *name){
    int i = 0;
    int i_ref = 0;
    int *ntc_len = (int *) malloc(sizeof(int));
    char *name_to_comp = (char *) malloc(sizeof(char));

    if (!ntc_len){printf("Erro! Falta de memoria");return -1;}
    if (!name_to_comp){printf("Erro! Falta de memoria");return -1;}

    *ntc_len = 1;
    *name_to_comp = '\0';
    
    while (data_base[i] != '\0')
    {
        if (data_base[i] != ';'){
            name_to_comp = add_char_to_string(name_to_comp, ntc_len, data_base[i]);
        } else {
            if (strcmp(name, name_to_comp) == 0){
                return i_ref;
            }
            i_ref = i + 1;
            name_to_comp = (char *) realloc(name_to_comp, sizeof(char));
            name_to_comp[0] = '\0';
            *ntc_len = 1;
        }
        i++;
    }

    free(ntc_len);
    free(name_to_comp);

    return -1;
}

char *add_name(char *data_base, int *length){
    printf("\nDigite o nome a ser adicionado: ");
    data_base = read_name(data_base, length);
    data_base = add_char_to_string(data_base, length, ';');
    return data_base;
}

char *remove_name(char *data_base, int *base_len) {
    
    int name_pos = 0;
    int letter_qty = 0;
    int i = 0;
    char *name_to_remove = (char *) malloc(sizeof(char));
    int *ntr_len = (int *) malloc(sizeof(int));
    
    if (!name_to_remove){printf("Erro! Falta de memoria");}
    if (!ntr_len){printf("Erro! Falta de memoria");}

    *name_to_remove = '\0';
    *ntr_len = 1;

    printf("\nDigite o nome a ser removido: ");
    name_to_remove = read_name(name_to_remove, ntr_len);

    letter_qty = *ntr_len - 1;

    name_pos = find_name(data_base, name_to_remove);

    if (name_pos >= 0) {
        while(i+name_pos != *base_len){
            if (data_base[i + name_pos + letter_qty + 1] == '\0'){
                break;
            } else {
                data_base[i + name_pos] = data_base[i + name_pos + letter_qty + 1]; 
            }
            i++;
        }
    
        data_base = (char *) realloc(data_base, sizeof(char) * (*base_len - *ntr_len));
        *base_len -= *ntr_len;
        data_base[*base_len-1] = '\0';
    }

    free(name_to_remove);
    free(ntr_len);

    return data_base;
}

void list_names(char *data_base, int base_length){
    int i = 0;

    printf("\nNomes disponíveis:\n\n");
    for (i = 0; i < base_length; i++){

        if (data_base[i] == ';') {
            printf("\n");
            continue;
        }

        if (data_base[i] == '\0'){break;}

        printf("%c", data_base[i]);
    }
}

int main(int argc, char const *argv[])
{
    char *data_base = (char *) malloc(sizeof(char));
    int *length = (int *) malloc(sizeof(int));
    int op = 0;
    
    if (!data_base){printf("Erro! Falta de memoria");return -1;}
    if (!length){printf("Erro! Falta de memoria");return -1;}
    
    *data_base = '\0';
    *length = 1;

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
            data_base = add_name(data_base, length);
            break;
        
        case 2:
            data_base = remove_name(data_base, length);
            break;

        case 3:
            list_names(data_base, *length);
            break;
        
        case 4:
            printf("\nAté logo!\n");
            break;

        default:
            printf("\n -> Digite uma opção válida! <-\n");
            break;
        }
    }
    
    free(data_base);
    free(length);

    return 0;
}
