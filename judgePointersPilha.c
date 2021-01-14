#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//stuct dos dados armazenados
typedef struct
{
    float entrada;
    struct Pilha *prox; 

}Pilha;

//struct de controle do empilhamento
typedef struct {
    int tamanho;
    Pilha* PointerTopo;
}Topo;

//inicia pilha
void start(Topo *p){
    p->tamanho = 0;
    p->PointerTopo= NULL;
}

//adciona dados na pilha
void add(Topo *p, float v){
    Pilha *new;//pilha nova
    new =(Pilha *) malloc(sizeof(Pilha));//alocacao de memoria pilha nova
    new->entrada = v; //armazenamento de dados recebe novo dado
    new->prox = p->PointerTopo; //ponteiro da pilha nova aponta para antigo topo
    p->PointerTopo = new; //topo aponta para novo topo
    p->tamanho++; //tamanho aumenta
}

//remove dados do empilhamento
void rem(Topo *p, float *v){
    Pilha *aux; //struct aux declarada
    aux = p->PointerTopo; //aux recebe apontador do topo
    if (p->tamanho == 0)
        return;
    else{
        *v = aux->entrada;
        p->PointerTopo = aux->prox;//topo volta para anterior
        p->tamanho--;
        free(aux);//libera memória
    }
    
}

float calculator(Pilha *p, char *rchar){
    float a, b, result;
    int i;

    for (i = 0; i < strlen(rchar); i++)//loop com o comprimento do char
    {
        if(rchar[i] < 65){//se char entra antes de 65 na tabela ascii
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