//declaração de bibliotecas
#include <stdlib.h>
 
//definindo const max
#define MAX 65536
 
//declaração de struct
typedef struct{
    //dados
}Cel;
 
//declaração do struct fila
typedef struct {
    Cel dado[MAX];
    int frente, tras, tam;
}Fila;
 
//função inicia fila
void Start(Fila *f){
    f->frente = 0;
    f->tras = f->frente;
    f->tam = 0;
}
 
//função insere dado na fila
void push(Fila *f, Cel novo){
    if(f->frente == (f->tras+1) % MAX){
        return;
    }
    f->dado[f->tras] = novo;
    f->tras = (f->tras+1)%MAX;
    f->tam++;
    return;
}
 
// função remove dado fila
void pop(Fila *f, Cel *a){
    if (f->frente != f->tras){
        *a = f->dado[f->frente];
        f->frente = (f->frente+1)%MAX;
        f->tam--;
    }
    return;
}
