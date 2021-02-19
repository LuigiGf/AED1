#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
typedef struct
{
    float entrada;
    struct Pilha *prox; 
 
}Pilha;
 
typedef struct {
    int tamanho;
    Pilha* PointerTopo;
}Topo;
 
void start(Topo *p){
    p->tamanho = 0;
    p->PointerTopo= NULL;
}
 
void add(Topo *p, float v){
    Pilha *new;
    new =(Pilha *) malloc(sizeof(Pilha));
    new->entrada = v;
    new->prox = p->PointerTopo;
    p->PointerTopo = new;
    p->tamanho++;
}
 
void rem(Topo *p, float *v){
    Pilha *aux;
    aux = p->PointerTopo;
    if (p->tamanho == 0)
        return;
    else{
        *v = aux->entrada;
        p->PointerTopo = aux->prox;
        p->tamanho--;
        free(aux);
    }
    
}
 
float calculator(Pilha *p, char *rchar){
    float a, b, result;
    int i;
 
    for (i = 0; i < strlen(rchar); i++)
    {
        if(rchar[i] < 65){
            rem(p, &b);
            rem(p, &a);
            switch (rchar[i])
            {
                case '+':
                    result = a + b;
                    break;
                
                case '-':
                    result = a - b;
                    break;
            
                case '*':
                    result = a * b;
                    break;
            
                case '/':
                    result = a / b;
                    break;
                
                default:
                    break;
            }
            add(p, result);
        }else{
            scanf("%f", &result);
            add(p, result);
        }
    }
    return result;
}
 
int main (void){
    char n[51];
    Topo entrada;
 
    start(&entrada);
    scanf("%s", &n);
    printf("%f", calculator(&entrada, n));
    return 0;
}