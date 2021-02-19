#include <stdlib.h>
 
typedef struct Celula Cel;
 
 //struct celula
struct Celula{
    Cel *prox;
    //dados
    int dado;
};
 
 //struct fila
typedef struct{
    Cel *frente, *tras;
    int tamanho;
}Fila;
 
 //funcao inicia fila
void Start(Fila *f){
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
}
 
 //funcao adiciona dado na fila
void Push(Fila *f, int dado){
    Cel *novo = (Cel *) malloc(sizeof(Cel)); 
 
    novo->prox = NULL;
    novo->dado = dado;
    if (f->tamanho == 0){
        f->frente = novo;
    }else{
        f->tras->prox = novo;
    }
        
    f->tras = novo;
    f->tamanho++;
}
 
//funcao remove dado da fila
void Pop(Fila *f, int *dado){
    Cel *Aux;
    if (f->tamanho == 0){
        return;
    }
    Aux = f->frente;
    *dado = f->frente->dado;
    f->frente = f->frente->prox;
    f->tamanho--;  
    free(Aux);
}
