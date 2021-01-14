#include <stdio.h>
#include <stdlib.h>

typedef struct produto
{
    int identificador;
    char nome[50];
    int qEstoque;
    float preco;
}Produto;

int main(void)
{
    Produto *produtos;
    int N;
    float valor;
    int estoque;
    printf("Insira o numero de produtos:");
    scanf("%d", &N);
    produtos = (Produto*) malloc(N * sizeof(Produto));
    for (int i = 0; i < N; i++)
    {
        produtos[i].identificador = i + 1;
        printf("Nome do produto:\n");
        scanf("%s", produtos[i].nome);
        printf("Quantidade em estoque e preco\n");
        scanf("%d %f", &produtos[i].qEstoque, &produtos[i].preco);
    }
    for (int i = 0; i < N; i++)
    {
        valor = 0;
        estoque = 0;
        if (produtos[i].preco > valor)
        {
            valor = produtos[i].preco;
        }
        if (produtos[i].qEstoque > estoque)
        {
            estoque = produtos[i].qEstoque;
        }
    }
    printf("O produto com maior valor eh: %d\n", valor);
    printf("O produto com maior estoque eh: %d\n", estoque);

    return 0;
}