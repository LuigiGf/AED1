#include <stdlib.h>
#include <stdio.h>

#define MAXVERTICES 100

typedef struct tadjacencia{
    int Vertice;
    int Aresta;
} TAdjacencia;

typedef struct listaCelula *ListaApontador;
typedef struct listaCelula {
    TAdjacencia adjacencias;
    ListaApontador anterior, proximo;
} ListaCelula;

typedef struct {
    ListaApontador ultimo;
    int tam;
} TADLista;

/* Inicia as variáveis da lista */
void ListaInicia(TADLista *pLista)
{
    pLista->ultimo = (ListaApontador) malloc(sizeof(ListaCelula));
    pLista->ultimo->proximo = pLista->ultimo;
    pLista->ultimo->anterior = pLista->ultimo;
    pLista->tam = 0;
}
/* Retorna se a lista está vazia */
int ListaVerificaVazia(TADLista *pLista)
{
    return (pLista->ultimo->proximo == pLista->ultimo);
}
/* Retorna o tamanho da lista */
int ListaTamanho(TADLista *pLista)
{
    return (pLista->tam);
}
/* Insere um item na lista na posicao apontada por p */
int ListaInsere(TADLista *pLista, ListaApontador p, TAdjacencia x)
{
    ListaApontador pNovo;
    if (p == NULL)
        return 0;
    pNovo = (ListaApontador) malloc(sizeof(ListaCelula));
    pNovo->adjacencias = x;
    pNovo->proximo = p;
    pNovo->anterior = p->anterior;
    p->anterior->proximo = pNovo;
    if (p->anterior == pLista->ultimo)
        pLista->ultimo = pNovo;
    p->anterior = pNovo;
    pLista->tam++;
    return 1;
}
/* Retira o item da lista da posicao apontada por p */
int ListaRetira(TADLista *pLista, ListaApontador p, TAdjacencia *pDados)
{
    ListaApontador pAux;
    if (ListaVerificaVazia(pLista))
        return 0;
    pAux = p;
    p->anterior->proximo = p->proximo;
    p->proximo->anterior = p->anterior;
    if (pAux == pLista->ultimo)
        pLista->ultimo = p->anterior;
    *pDados = pAux->adjacencias;
    free(pAux);
    pLista->tam--;
    return 1;
}
/* Retorna um apontador para o p-esimo item da lista */
ListaApontador ListaRetornaPosicao(TADLista *pLista, int p)
{
    ListaApontador pApontador;
    int Posicao;

    Posicao = 0;
    pApontador = pLista->ultimo->proximo->proximo;
    while ((pApontador != pLista->ultimo->proximo) && (Posicao != p))
    {
        pApontador = pApontador->proximo;
        Posicao++;
    }

    return pApontador;
}

//=======================================================================

//TAD GRAFO
typedef struct {
    TADLista Adj[MAXVERTICES];
    int NVertices;
    int NArestas;
} TADGrafo;
/* Inicia as variaveis do grafo */
int GrafoInicia(TADGrafo *pGrafo, int NVertices)
{
    int u;
    if (NVertices > MAXVERTICES)
        return 0;
    pGrafo->NVertices = NVertices;
    pGrafo->NArestas = 0;
    for (u = 0; u < pGrafo->NVertices; u++)
        ListaInicia(&pGrafo->Adj[u]);
return 1;
}
/* Retorna se existe a aresta (u, v) no grafo */
int GrafoExisteAresta(TADGrafo *pGrafo, int u, int v)
{
    TAdjacencia Adj;
    TADLista ListaAdj;
    int Existe;
    Existe = 0;
    ListaInicia(&ListaAdj);
    while (ListaRetira(&pGrafo->Adj[u], ListaRetornaPosicao(&pGrafo->Adj[u],ListaTamanho(&pGrafo->Adj[u])-1), &Adj)) {
        ListaInsere(&ListaAdj, ListaRetornaPosicao(&ListaAdj, ListaTamanho(&ListaAdj)), Adj);
        Existe = (Adj.Vertice == v);
        if (Existe)
            break;
    }
    while (ListaRetira(&ListaAdj, ListaRetornaPosicao(&ListaAdj, ListaTamanho(&ListaAdj)-1), &Adj))
        ListaInsere(&pGrafo->Adj[u], ListaRetornaPosicao(&pGrafo->Adj[u],ListaTamanho(&pGrafo->Adj[u])), Adj);
    return (Existe);
}
/* Insere a aresta e incidente aos vertices u e v no grafo */
int GrafoInsereAresta(TADGrafo *pGrafo, int u, int v, int e)
{
    TAdjacencia Adj;
    Adj.Vertice = v;
    Adj.Aresta = e;
    if (ListaInsere(&pGrafo->Adj[u], ListaRetornaPosicao(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u])), Adj)) {
        pGrafo->NArestas++;
        return 1;
    }
    else
        return 0;
}
/* Retira a aresta e incidente aos vertices u e v no grafo */
int GrafoRetiraAresta(TADGrafo *pGrafo, int u, int v, int *pE)
{
    TADLista ListaAdj;
    TAdjacencia Adj;
    int IncideAresta;
    IncideAresta = 0;
    ListaInicia(&ListaAdj);
    while (!IncideAresta && ListaRetira(&pGrafo->Adj[u], ListaRetornaPosicao(&pGrafo->Adj[u],ListaTamanho(&pGrafo->Adj[u])-1), &Adj))
        if (Adj.Vertice == v) {
            *pE = Adj.Aresta;
            pGrafo->NArestas--;
            IncideAresta = 1;
        }else
            ListaInsere(&ListaAdj, ListaRetornaPosicao(&ListaAdj, ListaTamanho(&ListaAdj)), Adj);
    while (ListaRetira(&ListaAdj, ListaRetornaPosicao(&ListaAdj, ListaTamanho(&ListaAdj)-1), &Adj))
        ListaInsere(&pGrafo->Adj[u], ListaRetornaPosicao(&ListaAdj, ListaTamanho(&pGrafo->Adj[u])), Adj);
    return IncideAresta;
}
/* Retorna a lista de adjacentes do vertice u no grafo */
TADLista *GrafoListaAdjacencia(TADGrafo *pGrafo, int u)
{
    TADLista *pLista, ListaAdj;
    TAdjacencia Adj;
    pLista = (TADLista *) malloc(sizeof(TADLista));
    ListaInicia(pLista);
    ListaInicia(&ListaAdj);
    while (ListaRetira(&pGrafo->Adj[u], ListaRetornaPosicao(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u])-1), &Adj))
        ListaInsere(&ListaAdj, ListaRetornaPosicao(&ListaAdj, ListaTamanho(&ListaAdj)), Adj);
    while (ListaRetira(&ListaAdj, ListaRetornaPosicao(&ListaAdj, ListaTamanho(&ListaAdj)-1), &Adj)) {
        ListaInsere(&pGrafo->Adj[u], ListaRetornaPosicao(&pGrafo->Adj[u], ListaTamanho(&pGrafo->Adj[u])), Adj);
        ListaInsere(pLista, ListaRetornaPosicao(pLista, ListaTamanho(pLista)), Adj);
    }
    return pLista;
}
/* Retorna o numero de vertices do grafo */
int GrafoNVertices(TADGrafo *pGrafo)
{
    return (pGrafo->NVertices);
}
/* Retorna o numero de arestas do grafo */
int GrafoNArestas(TADGrafo *pGrafo)
{
    return (pGrafo->NArestas);
}

int Dependencias(TADGrafo *grafo, int v) {
    int u, NumeroDeDependencias = 0;

    for (u = 0; u < grafo->NVertices; u++) {
        if (GrafoExisteAresta(grafo, u, v)){
            NumeroDeDependencias++;
        }
    }

    return NumeroDeDependencias;
}

int main(void) {
    TADGrafo grafo;
    TADLista *lista;

    int nPacotes, nDependeciasPacotes, i, u, v, dep;
    TAdjacencia aux;
    scanf("%d %d", &nPacotes, &nDependeciasPacotes);
    GrafoInicia(&grafo, nPacotes);

    for (i = 0; i < nDependeciasPacotes; i++) {
        scanf("%d %d", &u, &v);
        GrafoInsereAresta(&grafo, u - 1, v - 1, 2);
    }
  
    for (i = 0; i < nPacotes; i++) {
        dep = Dependencias(&grafo, i);
        lista = GrafoListaAdjacencia(&grafo, i);
        printf("%d %d %d", i + 1, dep, lista->tam);

        while(ListaRetira(lista, ListaRetornaPosicao(lista, 0), &aux) != 0) {
            printf(" %d", aux.Vertice + 1);
        }

        printf("\n");
    }

    return 0;
}