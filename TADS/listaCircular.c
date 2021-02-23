#include <stdlib.h>
 
 //item da celula
typedef struct {
    char dado;
}ListaItem;
 
typedef struct SCelula *Apontador;
 
 //celula com item e apontador para a proxima celula
typedef struct SCelula {
    ListaItem item;
    Apontador prox;
}ListaCelula;
 
 //lista com uma celula cabeça chamada ultimo e tamanho da lista
typedef struct{
    Apontador Ultimo;
    int tamanho;
}TADLista;
 
//inicia
void ListaInicia(TADLista *lista){
    lista->Ultimo = (Apontador) malloc(sizeof(ListaCelula));
    lista->Ultimo->prox = lista->Ultimo;
    lista->tamanho = 0;
}
 
//vazia
int ListaVerificaVazia(TADLista *lista){
    return (lista->Ultimo->prox == lista->Ultimo);
}
 
//retorna o tamanho
int ListaTamanho(TADLista *lista){
    return (lista->tamanho);
}
 
//adciona na lista
void ListaInsere(TADLista *lista, Apontador novo, ListaItem item){
    Apontador pAnterior, pNovo;
    
    pAnterior = lista->Ultimo->prox;
    while((pAnterior != lista->Ultimo) && (pAnterior->prox != novo)){
        pAnterior = pAnterior->prox;
    }
    if(pAnterior->prox != novo){
        return;
    }
    
    pNovo = (Apontador) malloc(sizeof(ListaCelula));
    pNovo->item = item;
    pNovo->prox = pAnterior->prox;
    pAnterior->prox = pNovo;
    if(pAnterior == lista->Ultimo){
        lista->Ultimo = pNovo;
    }
    lista->tamanho++;
}
 
//remove da lista
void ListaRemove(TADLista *lista, Apontador novo){
    Apontador Anterior, Aux;
 
    if(ListaVerificaVazia(lista)){
        return;
    }
 
    Anterior = lista->Ultimo->prox;
    while((Anterior != lista->Ultimo) && (Anterior->prox != novo)){
        Anterior = Anterior->prox;
    }
 
    if(Anterior->prox != novo){
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
Apontador ListaRetornaPosicao(TADLista *lista, int p){
    Apontador aux;
    int posicao = 0;
 
    aux = lista->Ultimo->prox->prox;
    while((aux != lista->Ultimo->prox) && (posicao != p)){
        aux = aux->prox;
        posicao++;
    }
 
    return aux;
}
