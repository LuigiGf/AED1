#include <stdlib.h>

typedef struct pilhaCelula *PilhaApontador;

typedef struct pilhaCelula{
    int item;
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

void PilhaRemove(TADPilha *pPilha, int pilhaitem){
    PilhaApontador pAux;

    if(PilhaVazia(pPilha)){
        return;
    }

    pAux = pPilha->ApontadorTopo;
    pPilha->ApontadorTopo = pAux->prox;
    pilhaitem = pAux->item;
    free(pAux);
    pPilha->tamanho--;

    return;
}
