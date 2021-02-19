#include <stdlib.h>
 
 //struct dos items a serem utilizados na celula
typedef struct{
    char entrada;
}Item;
 
typedef struct SCelula *Apontador;
 
 //struct da celula com os itens e apontador tanto para a proxima celula quanto para a celula anterior
typedef struct SCelula {
    Item item;
    Apontador Ant, Prox;
}Celula;
 
//struct lista com celula apontadora cabeça e tamanho
typedef struct{
    Apontador Ultimo;
    int tamanho;
}Lista;
 
//Inicia a lista
void Start(Lista *lista){
    lista->Ultimo = (Apontador) malloc(sizeof(Celula));
    lista->Ultimo->Prox = lista->Ultimo;
    lista->Ultimo->Ant = lista->Ultimo;
    lista->tamanho = 0;
}
 
//Retorna se a lista está vazia
int Empty(Lista *lista){
    return (lista->Ultimo->Prox == lista->Ultimo);
}
 
//Retorna o tamanho da lista
int Tam(Lista *lista){
    return (lista->tamanho);
}
 
//insere um item na lista, posicao position
void Push(Lista *lista, Apontador position, Item item){
    Apontador pNovo;
 
    if(position == NULL){
        return;
    }
 
    pNovo = (Apontador) malloc(sizeof(Celula));
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
void Pop(Lista *lista, Apontador position){
    Apontador pAux;
 
    if(Empty(lista)){
        return;
    }
 
    pAux = position;
    position->Ant->Prox = position->Prox;
    position->Prox->Ant = position->Ant;
 
    if(pAux == lista->Ultimo){
        lista->Ultimo = position->Ant;
    }
 
    free(pAux);
    lista->tamanho--;
}
 
//retorna um apontador para o numero da lista
Apontador listPosition(Lista *lista, int p){
    Apontador pApontador;
    int Posicao;
 
    Posicao = 0;
    pApontador = lista->Ultimo->Prox->Prox;
 
    while((pApontador != lista->Ultimo->Prox) && (Posicao != p)){
        pApontador = pApontador->Prox;
        Posicao++;
    }
 
    return pApontador;
}