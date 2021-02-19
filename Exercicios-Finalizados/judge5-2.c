#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct{
    char entrada;
}Item;
 
typedef struct SCelula *Apontador;
 
typedef struct SCelula {
    Item item;
    Apontador Ant, Prox;
}Celula;
 
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
 
    posicao = lista.Ultimo->Prox;
    for(i = 0; i < strlen(entrada); i++){
        switch (entrada[i])
        {
        //home = inicio da linha
        case '[':
            posicao = lista.Ultimo->Prox;
            break;
        //end = fim da linha
        case ']':
            posicao = lista.Ultimo;
            break;
        //apaga o anterior
        case '-':
            if(posicao != lista.Ultimo->Prox){
                pAux = posicao;
                pAux = pAux->Ant;
                Pop(&lista, posicao);
                posicao = pAux;
            }
            break;
        //passa o cursor para um anterior
        case '<':
            if(posicao != lista.Ultimo->Prox){
                pAux = posicao;
                pAux = pAux->Ant;
                posicao = pAux;
            }            
            break;
        //passa o cursor para frente se possivel
        case '>':
            if(posicao != lista.Ultimo){
                posicao = posicao->Prox;
            }
            break;
        //caso default pra nenhuma exceção
        default:
            armazenar.entrada = entrada[i];
            Push(&lista, posicao->Prox, armazenar);
            posicao = posicao->Prox;
            break;
        }
    }
 
    posicao = lista.Ultimo->Prox;
    //printar lista
    for(i = 0; i < Tam(&lista); i++){
        posicao = posicao->Prox;
        printf("%c", posicao->item);
    }
    return 0;
}