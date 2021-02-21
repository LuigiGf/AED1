//declaração de bibliotecas
#include <stdlib.h>
 
//definindo const max
#define MAX 65536
 
//declaração de struct
typedef struct{
    //dados
}TADFILACELULA;
 
//declaração do struct fila
typedef struct {
    TADFILACELULA dado[MAX];
    int frente, tras, tam;
}TADFILA;
 
//função inicia fila
void FilaInicia(TADFILA *f){
    f->frente = 0;
    f->tras = f->frente;
    f->tam = 0;
}
 
//função insere dado na fila
void FilaInsere(TADFILA *f, TADFILACELULA novo){
    if(f->frente == (f->tras+1) % MAX){
        return;
    }
    f->dado[f->tras] = novo;
    f->tras = (f->tras+1)%MAX;
    f->tam++;
    return;
}
 
// função remove dado fila
void FilaRemove(TADFILA *f, TADFILACELULA *a){
    if (f->frente != f->tras){
        *a = f->dado[f->frente];
        f->frente = (f->frente+1)%MAX;
        f->tam--;
    }
    return;
}
