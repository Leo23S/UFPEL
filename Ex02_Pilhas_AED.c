#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct Pessoa{
    char nome[30];
    int idade;
}Pessoa;

typedef struct Pilha{
    Pessoa pessoa[MAX];
    int base;
    int topo;
    int limite;
} Pilha;

Pessoa POP(Pilha *pilha);
void PUSH(Pilha *pilha, Pessoa pessoa);
void RESET(Pilha *pilha);
void Listar(Pilha *Pilha);

int main(){
    Pilha *pilha;
    pilha = malloc(sizeof(Pilha));

    RESET(pilha);
    Pessoa aluno;

    for (int i = 0; i < 5; i++){
        aluno.idade =  i*10;
        aluno.nome[0] = 'a';
        aluno.nome[1] = '\0';
        PUSH(pilha, aluno);
    }
    Listar(pilha);
    free(pilha);
}

Pessoa POP(Pilha *pilha){
    if (pilha->topo == 0){
        return;
    }else{
        pilha->topo -= 1;  
        return pilha->pessoa[pilha->topo];
    }
}

void PUSH(Pilha *pilha, Pessoa pessoa){
    if(pilha->topo == MAX){
        printf("pilha cheia");
        return;
    }else{
        pilha->pessoa[pilha->topo] = pessoa;
        pilha->topo++;
    }
}

void RESET(Pilha *pilha){
    pilha->topo = 0;
    pilha->base = 0;
    pilha->limite = 10;
}

void Listar(Pilha *pilha){
    Pilha *pilhaAux;
    pilhaAux = malloc(sizeof(Pilha));
    RESET(pilhaAux);

    Pessoa aluno;
    while (pilha->topo > 0){
        aluno = POP(pilha);
        PUSH(pilhaAux, aluno);
    }
    for (int i = 1; pilhaAux->topo > 0; i++){
        aluno = POP(pilhaAux);
        printf("aluno %d: idade: %d, nome %s\n", i, aluno.idade, aluno.nome);
        PUSH(pilha, aluno);
    }
    free(pilhaAux);
}