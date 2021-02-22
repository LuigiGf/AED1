#define MAXVERTICES 100
#define MAXARESTAS 5000

//struct de adjacencia com as arestas e suas incidencias
typedef struct {
    int IncideAresta;
    int Aresta;
} GrafoAdjacencia;

//struct do grafo com o numero de adjacencias e o numero de vertices e arestas
typedef struct {
    GrafoAdjacencia Adj[MAXVERTICES][MAXARESTAS];
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
    return;
}

//Verifica se ja existe aresta no grafo
int GrafoVerificaAresta(TADGrafo *pGrafo, int u, int v){
    int e;
    
    for(e = 0; e < pGrafo->nArestas; e++){
        if((pGrafo->Adj[u][e].IncideAresta > 0) && (pGrafo->Adj[v][e].IncideAresta < 0)){
            return 1;
        }
    }
    return 0;
}

//Insere Aresta aos vertices u e v
void GrafoInsereAresta(TADGrafo *pGrafo, int u, int v, int aresta){
    int i;

    if(pGrafo->nArestas >= MAXARESTAS){
        return;
    }

    for(i = 0; i < pGrafo->nVertices; i++){
        pGrafo->Adj[i][pGrafo->nArestas].IncideAresta = 0;
    }

    pGrafo->Adj[u][pGrafo->nArestas].IncideAresta = 1;
    pGrafo->Adj[v][pGrafo->nArestas].IncideAresta = -1;
    pGrafo->Adj[u][pGrafo->nArestas].Aresta = aresta;
    pGrafo->Adj[v][pGrafo->nArestas].Aresta = aresta;
    pGrafo->nArestas++;

    return;
}

//Retira aresta e incidente dos vertices u e v
void GrafoRemoveAresta(TADGrafo *pGrafo, int u, int v, int *pAresta){//*pAresta é a aresta removida que será armazenada na variável
    int i, e;

    if(! GrafoVerificaAresta(pGrafo, u, v)){
        return;
    }

    for(e = 0; e < pGrafo->nArestas; e++){
        if((pGrafo->Adj[u][e].IncideAresta > 0) && (pGrafo->Adj[v][e].IncideAresta < 0)){
            break;
        }
    }
    *pAresta = pGrafo->Adj[u][e].Aresta;
    for(i = 0; i < pGrafo->nVertices; i++){
        pGrafo->Adj[i][e] = pGrafo->Adj[i][pGrafo->nArestas-1];
    }
    pGrafo->nArestas--;

    return;
}

//Atenção a func abaixo necessita do TAD lista, caso ela seja necessaria basta incluir o TAD lista requisitado
//func que retorna a lista de adjacenctes do vertice u
/*TADLista *GrafoListaAdj(TADGrafo *pGrafo, int u){
    TADLista *pLista;
    int v, e;

    pLista = (TADLista *) malloc(sizeof(TADLista));
    ListaInicia(pLista);
    for(e = 0; e < pGrafo.nArestas; e++){
        if(pGrafo->Adj[u][e].IncideAresta > 0){
            for(v = 0; v < pGrafo->nVertices; v++){
                if(pGrafo->Adj[v][e].IncideAresta < 0){
                    ListaInsere(pLista, ListaTamanho(pLista), v);
                    break;
                }
            }
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