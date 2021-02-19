#include <stdlib.h>
 
 //item da celula
typedef struct {
    char dado;
}Item;
 
typedef struct SCelula *Apontador;
 
 //celula com item e apontador para a proxima celula
typedef struct SCelula {
    Item item;
    Apontador prox;
}Celula;
 
 //lista com uma celula cabeça chamada ultimo e tamanho da lista
typedef struct{
    Apontador Ultimo;
    int tamanho;
}Lista;
 
//inicia
void Start(Lista *lista){
    lista->Ultimo = (Apontador) malloc(sizeof(Celula));
    lista->Ultimo->prox = lista->Ultimo;
    lista->tamanho = 0;
}
 
//vazia
int Empty(Lista *lista){
    return (lista->Ultimo->prox == lista->Ultimo);
}
 
//retorna o tamanho
int Tam(Lista *lista){
    return (lista->tamanho);
}
 
//adciona na lista
void Push(Lista *lista, Apontador new, Item item){
    Apontador pAnterior, pNew;
    
    pAnterior = lista->Ultimo->prox;
    while((pAnterior != lista->Ultimo) && (pAnterior->prox != new)){
        pAnterior = pAnterior->prox;
    }
    if(pAnterior->prox != new){
        return;
    }
    
    pNew = (Apontador) malloc(sizeof(Celula));
    pNew->item = item;
    pNew->prox = pAnterior->prox;
    pAnterior->prox = pNew;
    if(pAnterior == lista->Ultimo){
        lista->Ultimo = pNew;
    }
    lista->tamanho++;
}
 
//remove da lista
void Pop(Lista *lista, Apontador new){
    Apontador Anterior, Aux;
 
    if(Empty(lista)){
        return;
    }
 
    Anterior = lista->Ultimo->prox;
    while((Anterior != lista->Ultimo) && (Anterior->prox != new)){
        Anterior = Anterior->prox;
    }
 
    if(Anterior->prox != new){
        return;
    }
 
    Aux = Anterior->prox;
    Anterior->prox = Aux->prox;
    
    if(Aux == lista->Ultimo){
        lista->Ultimo = Anterior;
    }
 
    free(Aux);
    lista->tamanho--;
}
 
//encontra uma posição
Apontador ReturnPosition(Lista *lista, int p){
    Apontador aux;
    int posicao = 0;
 
    aux = lista->Ultimo->prox->prox;
    while((aux != lista->Ultimo->prox) && (posicao != p)){
        aux = aux->prox;
        posicao++;
    }
 
    return aux;
}
