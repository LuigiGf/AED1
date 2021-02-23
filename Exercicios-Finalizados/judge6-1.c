#include <stdio.h>
#include <stdlib.h>

#define MAXVERTICES 100

typedef struct listacelula *ApontadorListaCelula;
typedef struct tadlista *ApontadorLista;

typedef struct listacelula{
    int Adj;
    ApontadorListaCelula anterior, proximo;
}ListaCelula;

typedef struct tadlista{
    ApontadorListaCelula ultimo;
    int tamanho;
}TADLista;

typedef struct {
    int Aresta;
    int IncideAresta;
} GrafoAdjacencia;

typedef struct {
    GrafoAdjacencia Adj[MAXVERTICES][MAXVERTICES];
    int nVertices;
    int nArestas;
} TADGrafo;


void ListaInicia(TADLista *lista) {
    lista->ultimo = (ApontadorListaCelula) malloc(sizeof(ListaCelula));

    lista->ultimo->proximo = lista->ultimo;
    lista->ultimo->anterior = lista->ultimo;
    lista->tamanho = 0;
}

int ListaInsere(TADLista *lista, ApontadorListaCelula posicao, int Adj) {
    ApontadorListaCelula novo;

    if (posicao == NULL) {
        return 0;
    }

    novo = (ApontadorListaCelula) malloc(sizeof(ListaCelula));
    novo->Adj = Adj;
    novo->proximo = posicao;
    novo->anterior = posicao->anterior;
    posicao->anterior->proximo = novo;

    if (posicao->anterior == lista->ultimo) {
        lista->ultimo = novo;
    }

    posicao->anterior = novo;
    lista->tamanho++;
    return 1;
}

int ListaRemove(TADLista *lista, ApontadorListaCelula posicao, int *Adj) {
    ApontadorListaCelula aux;

    if (lista->tamanho == 0) {
        return 0;
    }

    aux = posicao;
    posicao->anterior->proximo = posicao->proximo;
    posicao->proximo->anterior = posicao->anterior;

    if (aux == lista->ultimo) {
        lista->ultimo = posicao->anterior;
    }

    *Adj = aux->Adj;
    free (aux);
    lista->tamanho--;
    return 1;
}

ApontadorListaCelula ListaRetornaPosicao(TADLista *lista, int p) {
    ApontadorListaCelula pApontador;
    int posicao;

    posicao = 0;
    pApontador = lista->ultimo->proximo->proximo;

    while((pApontador != lista->ultimo->proximo) && (posicao != p)){
        pApontador = pApontador->proximo;
        posicao++;
    }
    
    return pApontador;
}

void ApagaLista(TADLista *lista) {

    ApontadorListaCelula aux = lista->ultimo->proximo->proximo;

    while (aux->proximo != lista->ultimo->proximo) {
        aux = aux->proximo;
        free(aux->anterior);
        lista->tamanho--;
    }

    free(aux);
}

int GrafoInicia(TADGrafo *grafo, int nVertices) {
    int u, v;

    if (nVertices > MAXVERTICES) {
        return 0;
    }

    grafo->nVertices = nVertices;
    grafo->nArestas = 0;

    for (u = 0; u < grafo->nVertices; u++) {
        for (v= 0; v < grafo->nVertices; v++) {
        grafo->Adj[u][v].IncideAresta = 0;
        }
    }

    return 1;
}

int GrafoVerificaAresta(TADGrafo *grafo, int u, int v) {
    return grafo->Adj[u][v].IncideAresta;
}

int GrafoAdicionaAresta(TADGrafo *grafo, int u, int v, int e) {
    grafo->Adj[u][v].IncideAresta = 1;
    grafo->Adj[u][v].Aresta = e;
    grafo->nArestas++;
    return 1;
}

int GrafoRemoveAresta(TADGrafo *grafo, int u, int v, int *e) {
    if (!GrafoVerificaAresta(grafo, u, v)) {
        return 0;
    }

    *e = grafo->Adj[u][v].Aresta;
    grafo->Adj[u][v].IncideAresta = 0;
    grafo->nArestas--;
    return 1;
}

ApontadorLista GrafoListaAdj(TADGrafo *grafo, int u) {
    ApontadorLista lista;
    int v;
    lista = (ApontadorLista) malloc(sizeof(TADLista));
    ListaInicia(lista);

    for (v = 0; v < grafo->nVertices; v++) {
        if (GrafoVerificaAresta(grafo, u, v)) {
        ListaInsere(lista, ListaRetornaPosicao(lista, lista->tamanho), v);
        }
    }

  return lista;
}

int Dependencias(TADGrafo *grafo, int v) {
    int u, NumeroDeDependencias = 0;

    for (u = 0; u < grafo->nVertices; u++) {
        if (GrafoVerificaAresta(grafo, u, v)){
            NumeroDeDependencias++;
        }
    }

    return NumeroDeDependencias;
}

int main(void) {
    TADGrafo grafo;
    TADLista *lista;

    int nPacotes, nDependeciasPacotes, i, u, v, aux = 0, dep;
    scanf("%d %d", &nPacotes, &nDependeciasPacotes);
    GrafoInicia(&grafo, nPacotes);

    for (i = 0; i < nDependeciasPacotes; i++) {
        scanf("%d %d", &u, &v);
        GrafoAdicionaAresta(&grafo, u - 1, v - 1, 2);
    }
  
    for (i = 0; i < nPacotes; i++) {
        dep = Dependencias(&grafo, i);
        lista = GrafoListaAdj(&grafo, i);
        printf("%d %d %d", i + 1, dep, lista->tamanho);

        while(ListaRemove(lista, ListaRetornaPosicao(lista, 0), &aux) != 0) {
            printf(" %d", aux + 1);
        }

        printf("\n");
    }

    return 0;
}