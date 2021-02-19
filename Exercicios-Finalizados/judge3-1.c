//declaração de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
//definindo const max
#define MAX 65536
 
//declaração de struct de dos lutadores
typedef struct{
    int indice;
    int forca, inicial;
}Cel;
 
//declaração do struct fila
typedef struct {
    Cel lutadores[MAX];
    int frente, tras , tam;
}Fila;
 
//função inicia fila
void Start(Fila *f){
    f->frente = 0;
    f->tras = f->frente;
    f->tam = 0;
}
 
//função insere dado na fila
void push(Fila *f, Cel novo){
    if(f->frente == (f->tras+1) % MAX){
        return;
    }
    f->lutadores[f->tras] = novo;
    f->tras = (f->tras+1)%MAX;
    f->tam++;
    return;
}
 
// função remove dado fila
void pop(Fila *f, Cel *a){
    if (f->frente != f->tras){
        *a = f->lutadores[f->frente];
        f->frente = (f->frente+1)%MAX;
        f->tam--;
    }
    return;
}
 
//função para instanciar uma nova celula com dados power auxiliar
Cel Create(int power, int indice, int start){
    Cel novo;
    novo.indice = indice;
    novo.forca = power;
    novo.inicial = start;
    return novo;
}
 
//função que executa o problema e resolve
void Result(Fila *f,int n, int k){
    int i, power;
    Cel aux1, aux2;
    for (i = 0; i < n; i++){
            scanf("%d", &power);
            push(f, Create(power, i+1, power));
        }
        while(f->tam != 1){
            pop(f, &aux1);
            pop(f, &aux2);
            if(aux1.forca >= aux2.forca){
                power = (aux1.forca - aux2.forca) + k;
                if(power < aux1.inicial){
                    push(f, Create(power, aux1.indice, aux1.inicial));
                }else{
                    push(f, Create(aux1.inicial, aux1.indice, aux1.inicial));
                }
            }else {
                power = (aux2.forca - aux1.forca) + k;
                if(power < aux2.inicial){
                    push(f, Create(power, aux2.indice, aux2.inicial));
                }else{
                    push(f, Create(aux2.inicial, aux2.indice, aux2.inicial));
                }
            }
        }
    pop(f, &aux1);
    printf("%d",aux1.indice);
}
 
int main (void){
    Fila fila;
    int i, n, k, total;
    Start(&fila);
    scanf("%d %d", &n, &k);
    n = pow(2, n);
    Result(&fila, n, k);
    return 0;
}