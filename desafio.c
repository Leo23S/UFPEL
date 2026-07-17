//Leonardo Jacobsen Schwalm
// Matrícula: 25200755

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_CARACTERES 100

typedef struct Agenda{
    char Nome[MAX_CARACTERES];
    char Descricao[MAX_CARACTERES];
    char Data_Limite[MAX_CARACTERES];
    char Categoria[MAX_CARACTERES];
    int Prioridade; 
    int Concluida;
    struct Agenda *Prox;  
} Tarefa;
void Inserir(Tarefa *Head);
void Buscar(Tarefa *Head);
void Listar(Tarefa * Dados);
void Editar(Tarefa *Head);
void Excluir(Tarefa * Head);
void Concluir(Tarefa *Head);
void Gravar_Tarefas(Tarefa *Head);

void Ler_Arquivo(Tarefa * Dados);
void Mostra_Tarefa(Tarefa * Tarefa);
void Ler_String(char Frase[MAX_CARACTERES]);
Tarefa * Procura_Tarefa(Tarefa *Head, char Busca[MAX_CARACTERES]);
int Menu();
int Menu_Edicao();
int Menu_Listagem();
Tarefa * Cria_Lista();
Tarefa * Tarefa_Anterior(Tarefa *Head, Tarefa *Tarefa_Atual);

int main(){
    int Operacao, Desligamento=0;
    Tarefa * Dados;
    Dados = Cria_Lista();
    
    Ler_Arquivo(Dados);
    while (Desligamento == 0){
        Operacao = Menu();
        switch (Operacao){
        case 1:
            Inserir(Dados);
        break;
        case 2:
            Buscar(Dados);
        break;
        case 3:
            Listar(Dados);
        break;
        case 4:
            Editar(Dados);
        break;
        case 5:
            Excluir(Dados);
        break;
        case 6:
            Concluir(Dados);
        break;
        case 7:
            Gravar_Tarefas(Dados);
        break;
        case 8: 
            Desligamento = 1;
        break;
        }
    }
}

void Inserir(Tarefa *Head){
    int i, Posicao_Encontrada=0, Data_Errada=0;
    Tarefa *Nova_Tarefa, *Ordem, *Teste;
    Nova_Tarefa = (Tarefa *)malloc(sizeof(Tarefa));

    printf("Insira o nome da tarefa: \n");
    Ler_String(Nova_Tarefa->Nome);
    printf("Insira a descricao da tarefa: \n");
    Ler_String(Nova_Tarefa->Descricao);
    printf("Insira a data limite da tarefa: \n");
    Ler_String(Nova_Tarefa->Data_Limite);
    do{ 
        for (i=0; i < 10; i++){
            if (i == 4 || i == 7){
                i++;
            }
            if (Nova_Tarefa->Data_Limite[4] != '-' || Nova_Tarefa->Data_Limite[7] != '-' || isdigit(Nova_Tarefa->Data_Limite[i]) == 0 || Nova_Tarefa->Data_Limite[10] != '\0' || ((Nova_Tarefa->Data_Limite[5] == '1') && (Nova_Tarefa->Data_Limite[6] > '2')) || Nova_Tarefa->Data_Limite[5] > '1' || ((Nova_Tarefa->Data_Limite[8] == '3') && (Nova_Tarefa->Data_Limite[9] > '1')) || Nova_Tarefa->Data_Limite[8] > '3'){
                
                Data_Errada = 1;
                printf("Formato invalido, por favor  escreve uma data limite no formato ISO\n");
                printf("Insira a data limite da tarefa: \n");
                Ler_String(Nova_Tarefa->Data_Limite);
                i=10;
            }else if (i==9){
                Data_Errada=0;
            }
        }
    }while(Data_Errada == 1);

    printf("Insira a categoria da tarefa: \n");
    Ler_String(Nova_Tarefa->Categoria);
    while (strcmp(Nova_Tarefa->Categoria, "Prova") != 0 && strcmp(Nova_Tarefa->Categoria, "Trabalho") != 0 && strcmp(Nova_Tarefa->Categoria, "Outra") != 0){
        printf("Categoria invalida, por favor escolha entre as categorias \"Prova\", \"Trabalho\" e \"Outra\"\n");
        printf("Insira a categoria da tarefa: \n");
        Ler_String(Nova_Tarefa->Categoria);
    }
    printf("Insira o nivel de prioridade da tarefa: \n");
    scanf("%d", &Nova_Tarefa->Prioridade);
    getchar();
    while ((Nova_Tarefa->Prioridade != 1) && (Nova_Tarefa->Prioridade != 2) && (Nova_Tarefa->Prioridade != 3)){
        printf("nivel de prioridade invalido, por favor escolha entre os niveis \"1\", \"2\" e \"3\"\n");
        printf("Insira o nivel de prioridade da tarefa: \n");
        scanf("%d", &Nova_Tarefa->Prioridade);
        getchar();
    }
    Nova_Tarefa->Concluida = 0;
    printf("Tarefa registrada!\n\n");

    Ordem = Head->Prox;
    Teste = Head;
    Posicao_Encontrada=0;
    while (Posicao_Encontrada == 0){
        if (strcmp(Nova_Tarefa->Data_Limite, Ordem->Data_Limite) < 0){
            do {if (Teste->Prox == Ordem){
                    Nova_Tarefa->Prox = Ordem;
                    Teste->Prox = Nova_Tarefa;
                    Posicao_Encontrada=1;
                }else{
                    Teste = Teste->Prox;
                }
            }while(Teste->Prox != Nova_Tarefa);
        }else if(strcmp(Nova_Tarefa->Data_Limite, Ordem->Data_Limite) > 0){
            if (Ordem->Prox != NULL){
                Ordem = Ordem->Prox;
            }else {
                Nova_Tarefa->Prox = Ordem->Prox;
                Ordem->Prox = Nova_Tarefa;
                Posicao_Encontrada=1;
            }
        }else if(Nova_Tarefa->Prioridade > Ordem->Prioridade){
            do {
                if (Teste->Prox == Ordem){
                    Nova_Tarefa->Prox = Ordem;
                    Teste->Prox = Nova_Tarefa;
                    Posicao_Encontrada=1;
                }else{
                    Teste = Teste->Prox;
                }
            }while(Teste->Prox != Nova_Tarefa);
        }else{  
            if (Ordem->Prox != NULL){
                Ordem = Ordem->Prox;
            }else {
                Nova_Tarefa->Prox = Ordem->Prox;
                Ordem->Prox = Nova_Tarefa;
                Posicao_Encontrada=1;
            }
        }
    }
    if (Head->Prox == NULL){
        Nova_Tarefa->Prox = Head->Prox;
        Head->Prox = Nova_Tarefa;
    }
}

void Buscar(Tarefa *Head){
    char Busca[MAX_CARACTERES];
    Tarefa *Tarefa_Buscada;
    printf("Qual o nome da tarefa a ser buscada?\n");
    Ler_String(Busca);
    Tarefa_Buscada = Procura_Tarefa(Head, Busca);
    if (Tarefa_Buscada == NULL){
        printf("nenhuma tarefa encontrada\n");
    }else{
        Mostra_Tarefa(Tarefa_Buscada);
    }
}

void Listar(Tarefa * Dados){
    int Operacao, Desligamento=0;

    while (Desligamento == 0){
        Operacao = Menu_Listagem();
        printf("Listando tarefas: \n");
        switch (Operacao){
        case 1:
            while (Dados->Prox != NULL){
            Mostra_Tarefa(Dados->Prox);
            Dados = Dados->Prox;
            Desligamento = 1;
            }
            
        break;
        case 2:
            while (Dados->Prox != NULL){
                if(Dados->Prox->Concluida == 1){
                    Mostra_Tarefa(Dados->Prox);
                }
                Dados = Dados->Prox;
                Desligamento = 1;
            }
        break;
        case 3:
            while (Dados->Prox != NULL){
                if(Dados->Prox->Concluida == 0){
                    Mostra_Tarefa(Dados->Prox);
                }
                Dados = Dados->Prox;
                Desligamento = 1;
            }
        break;
        case 4:
            Desligamento = 1;
        break;
        }
    }
    
    printf("\n");
}

void Editar(Tarefa *Head){
    int i, Operacao, Desligamento=0, Data_Errada=0, Posicao_Encontrada=0;
    char Edicao[MAX_CARACTERES];
    Tarefa *Tarefa_Editada, *Anterior, *Tarefa_Subtituta, *Ordem, *Teste; // Tarefa_Subtituta serve para reinserir a tarefa quando se edita a data limite
    Tarefa_Subtituta = (Tarefa *)malloc(sizeof(Tarefa));
    printf("Qual o nome da tarefa a ser editada?\n");
    Ler_String(Edicao);
    if ((Tarefa_Editada = Procura_Tarefa(Head, Edicao)) == NULL){
        printf("nenhuma tarefa encontrada\n");
    } else{
        printf("Tarefa encontrada:\n");
        Mostra_Tarefa(Tarefa_Editada);
        while (Desligamento == 0){
            Operacao = Menu_Edicao();
            switch (Operacao){
                case 1:
                printf("Insira o novo nome da tarefa: \n");
                Ler_String(Tarefa_Editada->Nome);
                Desligamento = 1;
            break;
                case 2:
                printf("Insira a nova descricao da tarefa: \n");
                Ler_String(Tarefa_Editada->Descricao);
                Desligamento = 1;
            break;
                case 3:
                printf("Insira a nova data limite da tarefa: \n");
                Ler_String(Tarefa_Editada->Data_Limite);
                Anterior = Tarefa_Anterior(Head, Tarefa_Editada);
                
                do{ 
                    for (i=0; i < 10; i++){
                        if (i == 4 || i == 7){
                            i++;
                        }
                        if (Tarefa_Editada->Data_Limite[4] != '-' || Tarefa_Editada->Data_Limite[7] != '-' || isdigit(Tarefa_Editada->Data_Limite[i]) == 0 || Tarefa_Editada->Data_Limite[10] != '\0' || ((Tarefa_Editada->Data_Limite[5] == '1') && (Tarefa_Editada->Data_Limite[6] > '2')) || Tarefa_Editada->Data_Limite[5] > '1' || ((Tarefa_Editada->Data_Limite[8] == '3') && (Tarefa_Editada->Data_Limite[9] > '1')) || Tarefa_Editada->Data_Limite[8] > '3'){
                            Data_Errada = 1;
                            printf("Formato invalido, por favor  escreve uma data limite no formato ISO\n");
                            printf("Insira a data limite da tarefa: \n");
                            Ler_String(Tarefa_Editada->Data_Limite);
                            i=10;
                        }else if (i==9){
                            Data_Errada=0;
                        }
                    }
                }while(Data_Errada == 1);
                
                strcpy(Tarefa_Subtituta->Nome, Tarefa_Editada->Nome);
                strcpy(Tarefa_Subtituta->Descricao, Tarefa_Editada->Descricao);
                strcpy(Tarefa_Subtituta->Data_Limite, Tarefa_Editada->Data_Limite);
                strcpy(Tarefa_Subtituta->Categoria, Tarefa_Editada->Categoria);
                Tarefa_Subtituta->Prioridade = Tarefa_Editada->Prioridade;
                Tarefa_Subtituta->Concluida = Tarefa_Editada->Concluida;

                Ordem = Head->Prox;
                Teste = Head;
                Posicao_Encontrada=0;
                while (Posicao_Encontrada == 0){
                    if (strcmp(Tarefa_Subtituta->Data_Limite, Ordem->Data_Limite) < 0){
                        do {if (Teste->Prox == Ordem){
                                Tarefa_Subtituta->Prox = Ordem;
                                Teste->Prox = Tarefa_Subtituta;
                                Posicao_Encontrada=1;
                            }else{
                                Teste = Teste->Prox;
                            }
                        }while(Teste->Prox != Tarefa_Subtituta);
                    }else if(strcmp(Tarefa_Subtituta->Data_Limite, Ordem->Data_Limite) > 0){
                        if (Ordem->Prox != NULL){
                            Ordem = Ordem->Prox;
                        }else {
                            Tarefa_Subtituta->Prox = Ordem->Prox;
                            Ordem->Prox = Tarefa_Subtituta;
                            Posicao_Encontrada=1;
                        }
                    }else if(Tarefa_Subtituta->Prioridade > Ordem->Prioridade){
                        do {
                            if (Teste->Prox == Ordem){
                                Tarefa_Subtituta->Prox = Ordem;
                                Teste->Prox = Tarefa_Subtituta;
                                Posicao_Encontrada=1;
                            }else{
                                Teste = Teste->Prox;
                            }
                        }while(Teste->Prox != Tarefa_Subtituta);
                    }else{  
                        if (Ordem->Prox != NULL){
                            Ordem = Ordem->Prox;
                        }else {
                            Tarefa_Subtituta->Prox = Ordem->Prox;
                            Ordem->Prox = Tarefa_Subtituta;
                            Posicao_Encontrada=1;
                        }
                    }
                }
                if (Head->Prox == NULL){
                    Tarefa_Subtituta->Prox = Head->Prox;
                    Head->Prox = Tarefa_Subtituta;
                }
                Desligamento = 1;
                free(Tarefa_Editada);
            break;
                case 4:
                printf("Insira a categoria da tarefa: \n");
                Ler_String(Tarefa_Editada->Categoria);
                while (strcmp(Tarefa_Editada->Categoria, "Prova") != 0 && strcmp(Tarefa_Editada->Categoria, "Trabalho") != 0 && strcmp(Tarefa_Editada->Categoria, "Outra") != 0){
                printf("Categoria invalida, por favor escolha entre as categorias \"Prova\", \"Trabalho\" e \"Outra\"\n");
                printf("Insira a categoria da tarefa: \n");
                Ler_String(Tarefa_Editada->Categoria);
                }
                Desligamento = 1;
            break;
                case 5:
                printf("Insira o nivel de prioridade da tarefa: \n");
                scanf("%d", Tarefa_Editada->Prioridade);
                getchar();
                while ((Tarefa_Editada->Prioridade != 1) && (Tarefa_Editada->Prioridade != 2) && (Tarefa_Editada->Prioridade != 3)){
                    printf("nivel de prioridade invalido, por favor escolha entre os niveis \"1\", \"2\" e \"3\"\n");
                    printf("Insira o nivel de prioridade da tarefa: \n");
                    scanf("%d", &Tarefa_Editada->Prioridade);
                    getchar();
                }
                Desligamento = 1;
            break;
                case 6:
                Desligamento = 1;
            break;
            }
        }
    }
}

void Excluir(Tarefa * Head){
    Tarefa *Tarefa_Excluida, *Anterior;
    char Exclusao[MAX_CARACTERES];
    printf("Qual o nome da tarefa a ser excluida?\n");
    Ler_String(Exclusao);
    Tarefa_Excluida = Procura_Tarefa(Head, Exclusao);
    if ( Tarefa_Excluida == NULL){
        printf("nenhuma tarefa encontrada\n");
    }else {
        Anterior = Tarefa_Anterior(Head, Tarefa_Excluida);
        Anterior->Prox = Tarefa_Excluida->Prox;
        free(Tarefa_Excluida);
        printf("Tarefa excluida com sucesso!\n");
    }
}

int Menu(){
    int Operacao, inicio=0;
    do {
        if ((Operacao <= 0 || Operacao > 8) && inicio == 1){
            printf("Operacao invalida, tente novamente\n");
        }
        printf("Qual Operacao deseja realizar?\n");
        printf("1. Inserir tarefa\n");
        printf("2. Buscar tarefa\n");
        printf("3. Listar tarefas\n");
        printf("4. Editar tarefa \n");
        printf("5. Excluir tarefa\n");
        printf("6. Concluir\n");
        printf("7. Gravar em arquivo\n");
        printf("8. Sair do programa\n");
        scanf("%d", &Operacao);
        getchar();
        inicio = 1;
    }while (Operacao <= 0 || Operacao > 8);
    return Operacao;
}

int Menu_Edicao(){
    int Operacao, inicio=0;
    do {
        if ((Operacao <= 0 || Operacao > 6) && inicio == 1){
            printf("Opcao invalida, tente novamente\n");
        }
        printf("Qual dado da tarefa deseja editar?\n");
        printf("1. Nome\n");
        printf("2. Descricao\n");
        printf("3. Data limite\n");
        printf("4. Categoria\n");
        printf("5. Prioridade\n");
        printf("6. Cancelar edicao\n");
        scanf("%d", &Operacao);
        getchar();
        inicio = 1;
    }while (Operacao <= 0 || Operacao > 6);
    return Operacao;
}

int Menu_Listagem(){
    int Operacao, inicio=0;
    do {
        if ((Operacao <= 0 || Operacao > 4) && inicio == 1){
            printf("Operacao invalida, tente novamente\n");
        }
        printf("Deseja listar as tarefas de que modo?\n");
        printf("1. Listar todas as tarefas\n");
        printf("2. Listar as tarefas concluidas\n");
        printf("3. Listar as tarefas nao concluidas\n");
        printf("4. Cancelar Listagem\n");
        scanf("%d", &Operacao);
        getchar();
        inicio = 1;
    }while (Operacao <= 0 || Operacao > 4);
    return Operacao;
}
void Ler_String(char Frase[MAX_CARACTERES]){
    Frase[0] = '\0'; 
    fgets(Frase, MAX_CARACTERES, stdin);
    Frase[strlen(Frase) - 1] = '\0';
}   

void Mostra_Tarefa(Tarefa *Tarefa){
    printf("Tarefa: %s\n", Tarefa->Nome);
    printf("Descricao: %s\n", Tarefa->Descricao);
    printf("Data Limite: %s\n", Tarefa->Data_Limite);
    printf("Categoria: %s\n", Tarefa->Categoria);
    printf("Prioridade: %d\n", Tarefa->Prioridade);
    if (Tarefa->Concluida == 0){
        printf("nao concluida\n\n");
    }else{
        printf("Concluida\n\n");
    }
}

Tarefa * Procura_Tarefa(Tarefa *Head, char Busca[MAX_CARACTERES]){
    Tarefa * Tarefa_Buscada;
    Tarefa_Buscada = Head->Prox;

    while (1){
        if (strcasecmp(Tarefa_Buscada->Nome, Busca) == 0){
            return Tarefa_Buscada;
        }else if (Tarefa_Buscada->Prox != NULL){
            Tarefa_Buscada = Tarefa_Buscada->Prox;
        }else {
            return NULL;
        }
    }
}

void Gravar_Tarefas(Tarefa *Head){
    Tarefa *Tarefa_Gravada;
    Tarefa_Gravada = Head->Prox;
    FILE *Arquivo = fopen("tarefas_out", "w");
    while (Tarefa_Gravada != NULL){
        fprintf(Arquivo, "%s|%s|%s|%s|%d|%d\n", Tarefa_Gravada->Nome, Tarefa_Gravada->Descricao, Tarefa_Gravada->Data_Limite, Tarefa_Gravada->Categoria, Tarefa_Gravada->Prioridade, Tarefa_Gravada->Concluida);
        Tarefa_Gravada = Tarefa_Gravada->Prox;
    }
    
    fclose(Arquivo);
}

void Ler_Arquivo(Tarefa *Head){
    char Nome[MAX_CARACTERES];
    int Primeira_Tarefa=1, Posicao_Encontrada=0;
    Tarefa *Nova_Tarefa, *Ordem, *Teste;
    
    FILE *Arquivo = fopen("tarefas_in.txt", "r");
    while ((fscanf(Arquivo, "%[^|]", Nome)) == 1){
        fgetc(Arquivo);

        Nova_Tarefa = (Tarefa *)malloc(sizeof(Tarefa));
        strcpy(Nova_Tarefa->Nome, Nome);
        
        fscanf(Arquivo, "%[^|]", Nova_Tarefa->Descricao);
        fgetc(Arquivo);
        fscanf(Arquivo, "%[^|]", Nova_Tarefa->Data_Limite);
        fgetc(Arquivo);
        fscanf(Arquivo, "%[^|]", Nova_Tarefa->Categoria);
        fgetc(Arquivo);
        fscanf(Arquivo, "%d", &Nova_Tarefa->Prioridade);
        fgetc(Arquivo);
        fscanf(Arquivo, "%d", &Nova_Tarefa->Concluida);
        fgetc(Arquivo);
        
        Ordem = Head->Prox;
        Teste = Head;
        Posicao_Encontrada=0;
        while (Posicao_Encontrada == 0 && Primeira_Tarefa == 0){
            if (strcmp(Nova_Tarefa->Data_Limite, Ordem->Data_Limite) < 0){
                do {if (Teste->Prox == Ordem){
                        Nova_Tarefa->Prox = Ordem;
                        Teste->Prox = Nova_Tarefa;
                        Posicao_Encontrada=1;
                    }else{
                        Teste = Teste->Prox;
                    }
                }while(Teste->Prox != Nova_Tarefa);
            }else if(strcmp(Nova_Tarefa->Data_Limite, Ordem->Data_Limite) > 0){
                if (Ordem->Prox != NULL){
                    Ordem = Ordem->Prox;
                }else {
                    Nova_Tarefa->Prox = Ordem->Prox;
                    Ordem->Prox = Nova_Tarefa;
                    Posicao_Encontrada=1;
                }
            }else if(Nova_Tarefa->Prioridade > Ordem->Prioridade){
                do {
                    if (Teste->Prox == Ordem){
                        Nova_Tarefa->Prox = Ordem;
                        Teste->Prox = Nova_Tarefa;
                        Posicao_Encontrada=1;
                    }else{
                        Teste = Teste->Prox;
                    }
                }while(Teste->Prox != Nova_Tarefa);
            }else{  
                if (Ordem->Prox != NULL){
                    Ordem = Ordem->Prox;
                }else {
                    Nova_Tarefa->Prox = Ordem->Prox;
                    Ordem->Prox = Nova_Tarefa;
                    Posicao_Encontrada=1;
                }
            }
        }
        if (Primeira_Tarefa == 1){
            Nova_Tarefa->Prox = Head->Prox;
            Head->Prox = Nova_Tarefa;
            Primeira_Tarefa = 0;
        }
    }
    fclose(Arquivo);
}

void Concluir(Tarefa *Head){
    char Conclusao[MAX_CARACTERES];
    Tarefa *Tarefa_Concluida;
    printf("qual tarefa deseja concluir?\n");
    Ler_String(Conclusao);
    Tarefa_Concluida = Procura_Tarefa(Head, Conclusao);
    if (Tarefa_Concluida == NULL){
        printf("nenhuma tarefa encontrada\n");
    }else{
        Tarefa_Concluida->Concluida = 1;
        printf("Tarefa concluida, parabens!\n\n");
    }
    
}

Tarefa * Cria_Lista(){
    Tarefa *Start;
	Start = (Tarefa *)malloc(sizeof(Tarefa));
	Start->Prox = NULL;
	return Start;
}

Tarefa * Tarefa_Anterior(Tarefa *Head, Tarefa *Tarefa_Atual){ //Função que retorna a tarefa que aponta para a tarefa passada
    Tarefa *Teste;
    Teste = Head;
    while (1){
        if (Teste->Prox == Tarefa_Atual){
            return Teste;
        }else if (Teste->Prox != NULL){
            Teste = Teste->Prox;
        }
    }
}