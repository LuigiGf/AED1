#define MAXVERTICES 100

//struct de adjacencia com as arestas e suas incidencias
typedef struct {
    int IncideAresta;
    int Aresta;
} GrafoAdjacencia;

//struct do grafo com o numero de adjacencias e o numero de vertices e arestas
typedef struct {
    GrafoAdjacencia Adj[MAXVERTICES][MAXVERTICES];
    int nVertices;
    int nArestas;
} TADGrafo;

//Inicia Grafo func
void GrafoInicia(TADGrafo *pGrafo, int NVertices){
    int u, v;

    if (NVertices > MAXVERTICES){
        return;
    }

    pGrafo->nVertices = NVertices;
    pGrafo->nArestas = 0;
    for(u = 0; u < pGrafo->nVertices; u++){
        for(v = 0; v < pGrafo->nVertices; v++){
            pGrafo->Adj[u][v].IncideAresta = 0;
        }
    }
    return;
}

//Verifica se ja existe aresta no grafo
int GrafoVerificaAresta(TADGrafo *pGrafo, int u, int v){
    return pGrafo->Adj[u][v].IncideAresta;
}

//Insere Aresta aos vertices u e v
void GrafoInsereAresta(TADGrafo *pGrafo, int u, int v, int aresta){
    pGrafo->Adj[u][v].IncideAresta = 1;
    pGrafo->Adj[u][v].Aresta = aresta;
    pGrafo->nArestas++;
    return;
}

//Retira aresta e incidente dos vertices u e v
void GrafoRemoveAresta(TADGrafo *pGrafo, int u, int v, int *pAresta){//*pAresta é a aresta removida que será armazenada na variável
    if(! GrafoVerificaAresta(pGrafo, u, v)){
        return;
    }

    *pAresta = pGrafo->Adj[u][v].Aresta;
    pGrafo->Adj[u][v].IncideAresta = 0;
    pGrafo->nArestas--;
    return;
}

//Atenção a func abaixo necessita do TAD lista, caso ela seja necessaria basta incluir o TAD lista requisitado
//func que retorna a lista de adjacenctes do vertice u
/*Lista *GrafoListaAdj(Grafo *pGrafo, int u){
    Lista *pLista;
    int v;

    pLista = (Lista *) malloc(sizeof(Lista));
    listaInicia(pLista);

    for(v = 0; v < pGrafo->nVertices; v++){
        if(GrafoVerificaAresta(pGrafo, u, v)){
            listaInsere(pLista, listaTamanho(pLista), v);
        }
    }
    return pLista;
}
*/

//retorna numero de vertices do grafo
int GrafoNVertices(TADGrafo *pGrafo){
    return (pGrafo->nVertices);
}

//retorna o numero de arestas do grafo
int GrafoNArestas(TADGrafo *pGrafo){
    return (pGrafo->nArestas);
}