#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Menu();

int main(){
    char *String = NULL, Nome_Aux[15], *Exclusao, *Substituicao;
    int Operacao=0;
    while(Operacao != -1){
        Menu();
        scanf("%d", &Operacao);
        switch (Operacao){
        case 1:
            printf("Digite o nome a ser adicionado:\n");
            scanf("%s", Nome_Aux);
            Nome_Aux[strlen(Nome_Aux)+1] = '\0';
            Nome_Aux[strlen(Nome_Aux)] = ';';
            String = realloc(String, (sizeof(String) + strlen(Nome_Aux)));
            strcat(String, Nome_Aux);
            break;
        case 2:
            printf("Digite o nome a ser excluido:\n");
            scanf("%s", Nome_Aux);
            Exclusao = strstr(String, Nome_Aux);
            Substituicao = strchr(Exclusao, ';');
            Substituicao++;
            strcpy(Exclusao, Substituicao);

            break;
        case 3:
            printf("String: %s\n", String);
            break;
        case 4:
            printf("opcao 4 escolhida\n");
            Operacao = -1;
            break;
        default:
            Operacao = 0;
            break;
        }
    }
}

void Menu(){
    printf("Menu:\n");
    printf("1-Adicionar nome:\n");
    printf("2-Excluir nome\n");
    printf("3-Listar \n");
    printf("4-Sair\n");
}