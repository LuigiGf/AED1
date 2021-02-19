#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
typedef struct {
    char dado;
}Item;
 
typedef struct SCelula *Apontador;
 
typedef struct SCelula {
    Item item;
    Apontador prox;
}Celula;
 
typedef struct{
    Apontador Ultimo;
    int tamanho;
}Lista;
 
//inicia
void Start(Lista *lista){
    lista->Ultimo = (Apontador) malloc(sizeof(Celula));
    lista->Ultimo->prox = lista->Ultimo;
    lista->tamanho = 0;
}
 
//vazia
int Empty(Lista *lista){
    return (lista->Ultimo->prox == lista->Ultimo);
}
 
//retorna o tamanho
int Tam(Lista *lista){
    return (lista->tamanho);
}
 
//adciona na lista
void Push(Lista *lista, Apontador new, Item item){
    Apontador pAnterior, pNew;
    
    pAnterior = lista->Ultimo->prox;
    while((pAnterior != lista->Ultimo) && (pAnterior->prox != new)){
        pAnterior = pAnterior->prox;
    }
    if(pAnterior->prox != new){
        return;
    }
    
    pNew = (Apontador) malloc(sizeof(Celula));
    pNew->item = item;
    pNew->prox = pAnterior->prox;
    pAnterior->prox = pNew;
    if(pAnterior == lista->Ultimo){
        lista->Ultimo = pNew;
    }
    lista->tamanho++;
}
 
//remove da lista
void Pop(Lista *lista, Apontador new){
    Apontador Anterior, Aux;
 
    if(Empty(lista)){
        return;
    }
 
    Anterior = lista->Ultimo->prox;
    while((Anterior != lista->Ultimo) && (Anterior->prox != new)){
        Anterior = Anterior->prox;
    }
 
    if(Anterior->prox != new){
        return;
    }
 
    Aux = Anterior->prox;
    Anterior->prox = Aux->prox;
    
    if(Aux == lista->Ultimo){
        lista->Ultimo = Anterior;
    }
 
    free(Aux);
    lista->tamanho--;
}
 
//encontra uma posição
Apontador ReturnPosition(Lista *lista, int p){
    Apontador aux;
    int posicao = 0;
 
    aux = lista->Ultimo->prox->prox;
    while((aux != lista->Ultimo->prox) && (posicao != p)){
        aux = aux->prox;
        posicao++;
    }
 
    return aux;
}
 
/*Tecla [ = home, tecla ] = end, tecla - = delete, tecla < seta esquerda, tecla > seta direita
fim do texto = \n
*/
 
int main(void){
    Lista lista; //criando lista
    Item armazenar; //struct do item para ser armazenado
    Apontador posicao, pAux; //aponta posicao atual e ponteiro auxiliar
 
    int i; //auxiliar do loop
    char entrada[50000], aux; // entrada total
    gets(entrada); //pega os dados ta entrada utilizando gets 
    /*
    for(i = 0; ; i++){
        scanf("%c", &aux);
        if(aux == '\n'){
            break;
        }
        entrada[i] = aux;
    }*/
    Start(&lista); //inicia a lista
 
    posicao = lista.Ultimo->prox;
    for(i = 0; i < strlen(entrada); i++){
        switch (entrada[i])
        {
        //home = inicio da linha
        case '[':
            posicao = lista.Ultimo->prox;
            break;
        //end = fim da linha
        case ']':
            posicao = lista.Ultimo;
            break;
        //apaga o anterior
        case '-':
            if(posicao != lista.Ultimo->prox){
                pAux = posicao;
                while(pAux->prox != posicao){
                    pAux = pAux->prox;
                }
                Pop(&lista, posicao);
                posicao = pAux;
            }
            break;
        //passa o cursor para um anterior
        case '<':
            if(posicao != lista.Ultimo->prox){
                pAux = posicao;
                while(pAux->prox != posicao){
                    pAux = pAux->prox;
                }
                posicao = pAux;
            }
            break;
        //passa o cursor para frente se possivel
        case '>':
            if(posicao != lista.Ultimo){
                posicao = posicao->prox;
            }
            break;
        //caso default pra nenhuma exceção
        default:
            armazenar.dado = entrada[i];
            Push(&lista, posicao->prox, armazenar);
            posicao = posicao->prox;
            //printf("posicao %c entrada%d\n", posicao->item, entrada[i]);
            break;
        }
    }
 
    posicao = lista.Ultimo->prox;
    for(i = 0; i < Tam(&lista); i++){
        posicao = posicao->prox;
        printf("%c", posicao->item);
    }
 
    return 0;
}