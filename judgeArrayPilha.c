#include <stdio.h>
#include <string.h>

//definindo struct
typedef struct
{
    float valor[50];
    int topo;
} Pilha;

//iniciando topo da pilha como 0
void start(Pilha *p){

    p->topo = 0;
}

//adicionando dados na pilha
void add(Pilha *p, float *v){

    if(p->topo==50)//verificação se pilha tem topo limite
        return;

    else{
        p->valor[p->topo] = *v;
        p->topo++;
        return;
    }
}

//remove topo da fila
void rem(Pilha *p, float *v){

    if (p->topo != 0)
    {
        p->topo--;
        *v = p->valor[p->topo];
        return;
    }

    else
    {
        return;
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
            add(p, &result);
        }else{
            scanf("%f", &result);
            add(p, &result);
        }
    }
    return result;
}

int main (void){
    Pilha entrada;
    char n[50];
    start(&entrada);
    scanf("%s", &n);
    printf("%f", calculator(&entrada, n));
    return 0;
}