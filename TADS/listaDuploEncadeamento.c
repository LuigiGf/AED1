#include <stdlib.h>
 
 //struct dos items a serem utilizados na celula
typedef struct{
    int entrada;
}ListaItem;
 
typedef struct ListaSCelula *ListaApontador;
 
 //struct da celula com os itens e apontador tanto para a proxima celula quanto para a celula anterior
typedef struct ListaSCelula {
    ListaItem item;
    ListaApontador Ant, Prox;
}ListaCelula;
 
//struct lista com celula apontadora cabeça e tamanho
typedef struct{
    ListaApontador Ultimo;
    int tamanho;
}TADLista;
 
//Inicia a lista
void ListaInicia(TADLista *lista){
    lista->Ultimo = (ListaApontador) malloc(sizeof(ListaCelula));
    lista->Ultimo->Prox = lista->Ultimo;
    lista->Ultimo->Ant = lista->Ultimo;
    lista->tamanho = 0;
}
 
//Retorna se a lista está vazia
int ListaVerificaVazia(TADLista *lista){
    return (lista->Ultimo->Prox == lista->Ultimo);
}
 
//Retorna o tamanho da lista
int ListaTamanho(TADLista *lista){
    return (lista->tamanho);
}
 
//insere um item na lista, posicao position
void ListaInsere(TADLista *lista, ListaApontador position, ListaItem item){
    ListaApontador pNovo;
 
    if(position == NULL){
        return;
    }
 
    pNovo = (ListaApontador) malloc(sizeof(ListaCelula));
    pNovo->item = item;
    pNovo->Prox = position;
    pNovo->Ant = position->Ant;
    position->Ant->Prox = pNovo;
 
    if(position->Ant == lista->Ultimo){
        lista->Ultimo = pNovo;
    }
 
    position->Ant = pNovo;
    lista->tamanho++;
}
 
//remove um item na lista, posicao position
void ListaRemove(TADLista *lista, ListaApontador position, ListaItem *pX){
    ListaApontador pAux;
 
    if(ListaVerificaVazia(lista)){
        return;
    }
 
    pAux = position;
    position->Ant->Prox = position->Prox;
    position->Prox->Ant = position->Ant;
 
    if(pAux == lista->Ultimo){
        lista->Ultimo = position->Ant;
    }
    *pX = pAux->item;
    free(pAux);
    lista->tamanho--;
    return;
}
 
//retorna um apontador para o numero da lista
ListaApontador ListaPosicao(TADLista *lista, int p){
    ListaApontador pApontador;
    int Posicao;
 
    Posicao = 0;
    pApontador = lista->Ultimo->Prox->Prox;
 
    while((pApontador != lista->Ultimo->Prox) && (Posicao != p)){
        pApontador = pApontador->Prox;
        Posicao++;
    }
 
    return pApontador;
}