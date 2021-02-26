#include <stdio.h>
#include <stdlib.h>
 
 //struct com os items e os nos de esquerda direita e conexao com o no pai
typedef struct arvoreNo{
    int item;
    struct arvoreNo *Pai, *esq, *dir;
}ArvoreNo;
 
//funcao que liga o nopai ao filho
int ArvoreNoPai(ArvoreNo *no, ArvoreNo *NoPai){
    if(NoPai==NULL){
        no=NULL;
        return 1;
    }
    if(no == NoPai->dir){
        NoPai->dir=no->dir;
    }else{
        NoPai->esq=no->dir;
    }
    return 0;
}
 
//funcao que cria um novo no
ArvoreNo *ArvoreNovoNo(int item, ArvoreNo *pai){
    ArvoreNo *Raiz;
    Raiz=(ArvoreNo*)malloc(sizeof(ArvoreNo));
    Raiz->item=item;
    Raiz->esq=NULL;
    Raiz->dir=NULL;
    Raiz->Pai=pai;
    return Raiz;
}
 
int ArvoreProcuraNo(ArvoreNo *pai, int x){

    if(pai == NULL){
        return 1;
    }
    else if(x < pai->item){
        return ArvoreProcuraNo(pai->esq, x);
    }
    else if(x > pai->item){
        return ArvoreProcuraNo(pai->dir, x);
    }
    else{
        return 0;
    }
}

ArvoreNo *ArvoreSelecionaNo(ArvoreNo *pai, int x){

    if(x < pai->item){
        return ArvoreSelecionaNo(pai->esq, x);
    }
    else if(x > pai->item){
        return ArvoreSelecionaNo(pai->dir, x);
    }
    else{
        return pai;
    }
}

ArvoreNo *minimo(ArvoreNo *NoMinimo){
    if(NoMinimo == NULL){   
       return NULL;   
    }else{   
          if( NoMinimo->esq == NULL ){   
              return NoMinimo;   
          }else{   
              return minimo(NoMinimo->esq);   
          }   
    }   
}
 
void ArvoreRemover(ArvoreNo **raiz, int x){   
    ArvoreNo *aux;   
    if(*raiz != NULL){   
       if(x < (*raiz)->item){    
           ArvoreRemover(&((*raiz)->esq), x);
       }else{   
            if(x > (*raiz)->item){    
                 ArvoreRemover(&((*raiz)->dir), x);    
             }else{ 
                if( (*raiz)->esq != NULL && (*raiz)->dir != NULL ){    
                     aux = minimo((*raiz)->dir);    
                     (*raiz)->item = (aux->item);   
                     ArvoreRemover(&(*raiz)->dir, (*raiz)->item);   
                }else{    
                       aux = *raiz;    
                       if((*raiz)->esq == NULL){    
                           *raiz = (*raiz)->dir;   
                       }    
                       else {   
                            *raiz = (*raiz)->esq;                          
                       }   
                free(aux);   
                }   
            }        
       }    
    }     
}
 
ArvoreNo *ArvoreInsere(ArvoreNo *NoAtual,int i){
    if(NoAtual==NULL){
        return ArvoreNovoNo(i,NULL);
    }
    if(NoAtual->dir!=NULL && i>NoAtual->item){
        ArvoreInsere(NoAtual->dir,i);
    }
    else if(NoAtual->dir==NULL && i>NoAtual->item){
        NoAtual->dir=ArvoreNovoNo(i,NoAtual);
    }
    else if(NoAtual->esq!=NULL && i<NoAtual->item){
        ArvoreInsere(NoAtual->esq,i);
    }
    else if(NoAtual->esq==NULL && i<NoAtual->item){
        NoAtual->esq=ArvoreNovoNo(i,NoAtual);
    }

    return NoAtual;
}
 
void PreOrdem(ArvoreNo *No)
{
    if (No != NULL) {
        printf("(C%d", No->item);
        PreOrdem(No->esq);
        if(No->esq == NULL){
            printf("()", No->item);
        }
        PreOrdem(No->dir);
        if(No->dir == NULL){
            printf("()", No->item);
        }
        printf(")");
    }
}
 
int main(){
    int entrada1, entrada2, i;
    ArvoreNo *Raiz=NULL, *noAuxiliar;
    
    scanf("%d", &entrada1);
 
    for(i = 0; i < entrada1; i++){
        scanf("%d", &entrada2);
        Raiz = ArvoreInsere(Raiz, entrada2);
    }

    scanf("%d", &entrada2);

    if(ArvoreProcuraNo(Raiz, entrada2) == 0){
        ArvoreRemover(&Raiz, entrada2);
    }else{
        Raiz = ArvoreInsere(Raiz, entrada2);
    }

    PreOrdem(Raiz);
    return 0;
}