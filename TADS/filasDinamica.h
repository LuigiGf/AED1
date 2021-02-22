#include <stdlib.h>
 
typedef struct Celula TADCELFILA;
 
 //struct celula
struct Celula{
    TADCELFILA *prox;
    //dados
    int dado;
};
 
 //struct fila
typedef struct{
    TADCELFILA *frente, *tras;
    int tamanho;
}TADFILA;
 
 //funcao inicia fila
void FilaInicia(TADFILA *f){
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
}
 
 //funcao adiciona dado na fila
void FilaInsere(TADFILA *f, int dado){
    TADCELFILA *novo = (TADCELFILA *) malloc(sizeof(TADCELFILA)); 
 
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
void FilaRemove(TADFILA *f, int *dado){
    TADCELFILA *Aux;
    if (f->tamanho == 0){
        return;
    }
    Aux = f->frente;
    *dado = f->frente->dado;
    f->frente = f->frente->prox;
    f->tamanho--;  
    free(Aux);
}
