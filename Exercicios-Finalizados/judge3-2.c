#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct Celula Cel;
 
struct Celula{
    int Indice, Power, FInicial;
    Cel *prox;
};
 
typedef struct{
    Cel *frente, *tras;
    int tamanho;
}Fila;
 
void Start(Fila *f){
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
}
 
void Push(Fila *f, int Indice, int P, int FInicial){
    Cel *novo = (Cel *) malloc(sizeof(Cel)); 
 
    novo->prox = NULL;
    novo->Indice = Indice;
    novo->Power = P;
    novo->FInicial = FInicial;
    if (f->tamanho == 0){
        f->frente = novo;
    }else{
        f->tras->prox = novo;
    }
        
    f->tras = novo;
    f->tamanho++;
}
 
void Pop(Fila *f, int *Indice, int *Power, int *FInicial){
    Cel *Aux;
    if (f->tamanho == 0){
        return;
    }
    Aux = f->frente;
    *Indice = f->frente->Indice;
    *Power = f->frente->Power;
    *FInicial = f->frente->FInicial;
    f->frente = f->frente->prox;
    f->tamanho--;  
    free(Aux);
}
 
void Winner(Fila *f, int n, int k){
    int i, Power, F1, F2, Indice1, Indice2, FInicial1, FInicial2;
 
    for (i=0; i < n; i++){
        scanf("%d",&Power);
        Push(f, Power, i+1, Power);
    }
 
    while (f->tamanho > 1){
        Pop(f, &F1, &Indice1, &FInicial1);
        Pop(f, &F2, &Indice2, &FInicial2);
        if (F1 >= F2){
            Power = (F1 - F2) + k;
            if (Power < FInicial1){
                Push(f, Power, Indice1, FInicial1);
            }else{
                Push(f, FInicial1, Indice1, FInicial1);
            }
        }else{                            
            Power = (F2 - F1) + k;
            if (Power < FInicial2){
                Push(f, Power, Indice2, FInicial2);
            }else{
                Push(f, FInicial2, Indice2, FInicial2);
            }
        }
    }
    
    Pop(f, &F1, &Indice1, &FInicial1);
    printf("%d\n",Indice1);
}
 
int main(void){
    Fila Fila;
    int N, K;
 
    Start(&Fila);
    scanf("%d %d",&N, &K);
    N = pow(2, N);
    Winner(&Fila, N, K);
 
    return 0;
}