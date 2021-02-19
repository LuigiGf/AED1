#include <stdlib.h>

typedef struct
{
    float entrada;
    struct Pilha *prox; 
 
}Pilha;
 
typedef struct {
    int tamanho;
    Pilha* PointerTopo;
}Topo;
 
void start(Topo *p){
    p->tamanho = 0;
    p->PointerTopo= NULL;
}
 
void add(Topo *p, float v){
    Pilha *new;
    new =(Pilha *) malloc(sizeof(Pilha));
    new->entrada = v;
    new->prox = p->PointerTopo;
    p->PointerTopo = new;
    p->tamanho++;
}
 
void rem(Topo *p, float *v){
    Pilha *aux;
    aux = p->PointerTopo;
    if (p->tamanho == 0)
        return;
    else{
        *v = aux->entrada;
        p->PointerTopo = aux->prox;
        p->tamanho--;
        free(aux);
    }
}