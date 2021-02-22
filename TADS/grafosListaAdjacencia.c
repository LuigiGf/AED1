#include <stdlib.h>

#define MAXVERTICES 100

typedef struct grafoAdjacencia ListaItem;

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

//este TAD EXIGE O TAD LISTA
typedef struct grafoAdjacencia{
    int Vertice;
    int Aresta;
} GrafoAdjacencia;

typedef struct {
    TADLista Adj[MAXVERTICES];
    int NVertices;
    int NArestas;
}TADGrafo;

 
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
int ListaInsere(TADLista *lista, ListaApontador position, ListaItem item){
    ListaApontador pNovo;
 
    if(position == NULL){
        return 0;
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
    return 1;
}
 
//remove um item na lista, posicao position
int ListaRemove(TADLista *lista, ListaApontador position, ListaItem *pX){
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
    *pX = pAux->item;
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

//Inicia TADGrafo com uma lista de arestas para cada vertice
void GrafoInicia(TADGrafo *pGrafo, int NVertices){
    int u;

    if(NVertices > MAXVERTICES){
        return;
    }

    pGrafo->NVertices = NVertices;
    pGrafo->NArestas = NVertices;
    for(u = 0; u < pGrafo->NVertices; u++){
        ListaInicia(&pGrafo->Adj[u]);
    }

    return;
}

//Verifica se existe aresta no grafo
int GrafoVerificaAresta(TADGrafo *pGrafo, int u, int v){
    GrafoAdjacencia Adj;
    TADLista listaAdj;
    int existe;

    existe = 0;
    ListaInicia(&listaAdj);
    while(ListaRemove(&pGrafo->Adj[u], (ListaTamanho(&pGrafo->Adj[u]) - 1), &Adj)){
        ListaInsere(&listaAdj, ListaTamanho(&pGrafo->Adj[u]), Adj);
        existe = (Adj.Vertice == v);
        if(existe){
            break;
        }
    }
    while (ListaRemove(&listaAdj, ListaTamanho(&listaAdj)-1,&Adj)){
        ListaInsere(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u]), Adj);
    }
    return (existe);
}

//insere a aresta
int GrafoInsereAresta(TADGrafo *pGrafo, int u, int v, int e){
    GrafoAdjacencia Adj;

    Adj.Vertice = v;
    Adj.Aresta = e;
    if(ListaInsere(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u]), Adj)){
        pGrafo->NArestas++;
        return 1;
    }
    else{
        return 0;
    }
}

//remove a aresta
int GrafoRemoveAresta(TADGrafo *pGrafo, int u, int v, int *pE){
    TADLista ListaAdj;
    GrafoAdjacencia Adj;
    int IncideAresta;

    IncideAresta = 0;
    ListaInicia(&ListaAdj);
    while(!IncideAresta && ListaRemove(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u])-1, &Adj)){
        if(Adj.Vertice == v){
            *pE = Adj.Aresta;
            pGrafo->NArestas--;
            IncideAresta = 1;
        }else{
            ListaInsere(&ListaAdj, ListaTamanho(&ListaAdj), Adj);
        }
    }
    while(ListaRemove(&ListaAdj, ListaTamanho(&ListaAdj) - 1, &Adj)){
        ListaInsere(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u]), Adj);
    }
    return IncideAresta;
}

//retorna a lista de adjacentes do vertice
TADLista *GrafoListaAdj(TADGrafo *pGrafo, int u){
    TADLista *pLista, listaAdj;
    GrafoAdjacencia Adj;

    pLista = (TADLista *) malloc (sizeof(TADLista));
    ListaInicia(pLista);

    ListaInicia(&listaAdj);
    while(ListaRemove(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u])-1, &Adj)){
        ListaInsere(&listaAdj, ListaTamanho(&listaAdj), Adj);
    }

    while(ListaRemove(&listaAdj, ListaTamanho(&listaAdj)-1, &Adj)){
        ListaInsere(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u]), Adj);
        ListaInsere(pLista, ListaTamanho(pLista), Adj);
    }

    return pLista;
}

//Retorna o numero de vertices do grafo
int GrafoNVertices(TADGrafo *pGrafo){
    return (pGrafo->NVertices);
}

//Retorna o numero de arestas do grafo
int GrafoNArestas(TADGrafo *pGrafo){
    return (pGrafo->NArestas);
}
