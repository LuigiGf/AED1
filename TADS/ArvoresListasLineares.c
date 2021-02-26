#include <stdlib.h>

typedef struct {
    int Chave;
    /* outros componentes */
} ArvoreDados;

typedef struct ListaSCelula *ListaApontador;
//struct da celula com os itens e apontador tanto para a proxima celula quanto para a celula anterior
typedef struct ListaSCelula {
    ArvoreDados item;
    ListaApontador Ant, Prox;
}ListaCelula;
 
//struct lista com celula apontadora cabeça e tamanho
typedef struct{
    ListaApontador Ultimo;
    int tamanho;
}TADLista;

typedef struct arvoreNo *TArvore;

typedef struct arvoreNo {
    ArvoreDados Dados;
    TADLista Filhos;
} ArvoreNo;

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
int ListaInsere(TADLista *lista, ListaApontador position, TArvore item){
    ListaApontador pNovo;
 
    if(position == NULL){
        return 0;
    }
 
    pNovo = (ListaApontador) malloc(sizeof(ListaCelula));
    pNovo->item = item->Dados;
    pNovo->Prox = position;
    pNovo->Ant = position->Ant;
    position->Ant->Prox = pNovo;
 
    if(position->Ant == lista->Ultimo){
        lista->Ultimo = pNovo;
    }
 
    position->Ant = pNovo;
    lista->tamanho++;
    return 1;
}
 
//remove um item na lista, posicao position
int ListaRemove(TADLista *lista, ListaApontador position, TArvore pX){
    ListaApontador pAux;
 
    if(ListaVerificaVazia(lista)){
        return 0;
    }
 
    pAux = position;
    position->Ant->Prox = position->Prox;
    position->Prox->Ant = position->Ant;
 
    if(pAux == lista->Ultimo){
        lista->Ultimo = position->Ant;
    }
    pX->Dados = pAux->item;
    free(pAux);
    lista->tamanho--;
    return 1;
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

/* Inicia as variaveis da arvore */
void ArvoreInicia(TArvore Arvore, ArvoreDados x)
{
    Arvore->Dados = x;
    ListaInicia(&Arvore->Filhos);
}
/* Retorna se a arvore nao possui nenhum descendente */
int ArvoreVerificaFilho(TArvore Arvore)
{
    return (ListaTamanho(&Arvore->Filhos) == 0);
}
/* Retorna o numero de descendentes da arvore */
int ArvoreNFilhos(TArvore Arvore)
{
    return ListaTamanho(&Arvore->Filhos);
}
/* Insere uma subarvore como descendente da raiz da arvore */
int ArvoreInsere(TArvore Arvore, TArvore SubArv)
{
    return ListaInsere(&Arvore->Filhos, ListaPosicao(&Arvore->Filhos, ListaTamanho(&Arvore->Filhos)), SubArv);
}
/* Retorna a lista de descendentes da raiz da arvore */
TADLista *ArvoreListaFilhos(TArvore Arvore)
{
    TADLista *pLista, ListaArv;
    TArvore Arv;
    pLista = (TADLista *) malloc(sizeof(TADLista));
    ListaInicia(pLista);
    ListaInicia(&ListaArv);
    while (ListaRemove(&Arvore->Filhos, ListaPosicao(&Arvore->Filhos, ListaTamanho(&Arvore->Filhos)-1), Arv))
        ListaInsere(&ListaArv, ListaPosicao(&ListaArv, ListaTamanho(&ListaArv)), Arv);
    while (ListaRemove(&ListaArv, ListaPosicao(&ListaArv, ListaTamanho(&ListaArv)-1), Arv)) {
        ListaInsere(&Arvore->Filhos, ListaPosicao(&Arvore->Filhos, ListaTamanho(&Arvore->Filhos)), Arv);
        ListaInsere(pLista, ListaPosicao(pLista, ListaTamanho(pLista)), Arv);
    }
    return pLista;
}

