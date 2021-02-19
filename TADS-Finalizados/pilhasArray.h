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
 
void add(Pilha *p, float *v){
 
    if(p->topo==50)
        return;
 
    else{
        p->valor[p->topo] = *v;
        p->topo++;
        return;
    }
}
 
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