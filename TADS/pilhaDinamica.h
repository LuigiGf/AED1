#include <stdlib.h>

typedef struct {
    //dados
    int exemplo;
}PilhaItem;

typedef struct PilhaCelula *PilhaApontador;

typedef struct {
    PilhaItem item;
    PilhaApontador prox;
}PilhaCelula;

typedef struct {
    PilhaApontador ApontadorTopo;
    int tamanho;
}TADPilha;

void PilhaInicia(TADPilha *pPilha){
    pPilha->tamanho = 0;
    pPilha->ApontadorTopo = NULL;
}

int PilhaVazia (TADPilha *pPilha){
    return (pPilha->ApontadorTopo == NULL);
}

int PilhaTamanho(TADPilha *pPilha){
    return pPilha->tamanho;
}

void PilhaInsere(TADPilha *pPilha, int entradaExemplo){
    PilhaApontador pCelulaNova;

    pCelulaNova = (PilhaApontador) malloc(sizeof(PilhaCelula));
    pCelulaNova->item = entradaExemplo;
    pCelulaNova->prox = pPilha->ApontadorTopo;
    pPilha->ApontadorTopo = pCelulaNova;
    pPilha->tamanho++;
    return;
}

void PilhaRemove(TADPilha *pPilha, PilhaItem *pilhaitem){
    PilhaApontador pAux;

    if(PilhaVazia(pPilha)){
        return;
    }

    pAux = pPilha->ApontadorTopo;
    pPilha->ApontadorTopo = pAux->Prox;
    *pilhaitem = pAux->item;
    free(pAux);
    pPilha->tamanho--;

    return;
}
