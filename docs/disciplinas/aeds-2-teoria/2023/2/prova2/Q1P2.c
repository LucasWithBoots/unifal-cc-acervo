#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * O presente programa tem como objetivo implementar as operações de uma árvore
 * binária de busca.
 * Seu trabalho é implementar versões iterativas para as funções busca e
 * busca_pai (que são originalmente recursivas no código).
 *
 * Importante: ao executar o programa compilado você deve utilizar-se do script executar.sh.
 * Exemplo: supondo que você tenha compilado o código fonte da seguinte forma:
 * gcc Q1.c -o Q1
 *
 * Você deve chamar o script da seguinte forma:
 * ./executar.sh Q1
 *
 * Ou seja, o nome do executável gerado deve ser passado como argumento para o script.
 * Neste caso, Q1.
 *
 * Dentro do diretório você encontrará diversos casos de teste, nomeados como:
 *  - entrada_1.txt
 *  - entrada_2.txt
 *  ...
 *
 * Para cada arquivo de entrada existirá um gabarito correspondente. ou Seja:
 *  - gabarito_1.txt
 *  - gabarito_2.txt
 *  ...
 *
 *  Você NÃO deve alterar estes arquivos.
 *
 * Ao executar o script executar.sh ele comparará a saída produzida pelo seu programa com os gabaritos.
 * Você terá o resultado do teste para cada entrada.
 */

typedef struct noArvore_
{
    int valor;
    struct noArvore_ *esq;
    struct noArvore_ *dir;
} noArvore;

// noArvore *busca(noArvore *raiz, int k)
// {
//     if (raiz == NULL || raiz->valor == k)
//     {
//         return raiz;
//     }
//     if (k > raiz->valor)
//     {
//         return busca(raiz->dir, k);
//     }
//     else
//     {
//         return busca(raiz->esq, k);
//     }
// }

/**
 * implemente a seguir uma versão iterativa da função busca.
 * Utilize no máximo 6 ;.
 */
noArvore *busca(noArvore *raiz, int k)
{
    while(raiz != NULL && raiz->valor != k){
        if(k > raiz->valor){
            raiz = raiz->dir;
        }else{
            raiz = raiz->esq;
        }
    }
    return raiz;
}

// noArvore *buscaPai(noArvore *raiz, noArvore *n)
// {
//     if (raiz == NULL || raiz == n)
//     {
//         return NULL;
//     }

//     if (raiz->esq == n || raiz->dir == n)
//     {
//         return raiz;
//     }
//     if (n->valor > raiz->valor)
//     {
//         return buscaPai(raiz->dir, n);
//     }
//     else
//     {
//         return buscaPai(raiz->esq, n);
//     }
// }
/**
 * Implemente a seguir uma versão iterativa da função buscaPai.
 * Utilize no máximo 8 ;.
 */
noArvore *buscaPai(noArvore *raiz, noArvore *n)
{
    while(raiz != NULL){
        if(raiz -> esq == n || raiz -> dir == n){
            return raiz;
        }
        if(n -> valor > raiz -> valor){
            raiz = raiz->dir;
        }else{
            raiz = raiz -> esq;
        }
    }
    //linha acrescentada apenas para não dar erro de compilação.
    return NULL;
}

noArvore *insere(noArvore *raiz, noArvore *n)
{
    if (raiz == NULL)
    {
        return n;
    }
    if (n -> valor > raiz -> valor)
    {
        raiz -> dir = insere(raiz -> dir, n);
    }
    else
    {
        raiz -> esq = insere(raiz -> esq, n);
    }

    return raiz;
}

noArvore *removeRaiz(noArvore *raiz)
{
    noArvore *p, *q;

    if (raiz->esq == NULL)
    {
        q = raiz->dir;
        free(raiz);
        return (q);
    }

    p = raiz;
    q = raiz->esq;

    while (q->dir != NULL)
    {
        p = q;
        q = q->dir;
    }
    // repare que q é o nó anterior a r
    // na ordem e-r-d
    // enquanto que p é o pai de q
    if (p != raiz)
    {
        p->dir = q->esq;
        q->esq = raiz->esq;
    }
    q->dir = raiz->dir;
    free(raiz);
    return q;
}

noArvore *removeNo(noArvore *raiz, int valor)
{
    noArvore *n = busca(raiz, valor);

    if (n != NULL)
    {
        noArvore *pai = buscaPai(raiz, n);
        if (pai != NULL)
        {
            if (pai->dir == n)
            {
                pai->dir = removeRaiz(n);
            }
            else
            {
                pai->esq = removeRaiz(n);
            }
        }
        else
        {
            raiz = removeRaiz(n);
        }
    }
    return raiz;
}

void imprimePreOrdem(noArvore *raiz, char *arq_saida)
{

    if (raiz != NULL)
    {
        FILE *saida = fopen(arq_saida, "a");
        fprintf(saida, "%d ", raiz->valor);
        fclose(saida);
        if (raiz->esq != NULL)
        {
            imprimePreOrdem(raiz->esq, arq_saida);
        }
        if (raiz->dir != NULL)
        {
            imprimePreOrdem(raiz->dir, arq_saida);
        }
    }
}

noArvore *alocaNo(int valor)
{
    noArvore *novo_no = (noArvore *)malloc(sizeof(noArvore));
    novo_no->valor = valor;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}

void desalocaArvore(noArvore *raiz)
{
    if (raiz != NULL)
    {
        if (raiz->esq != NULL)
        {
            desalocaArvore(raiz->esq);
        }
        if (raiz->dir != NULL)
        {
            desalocaArvore(raiz->dir);
        }
        free(raiz);
    }
}

void gera_nomes_arquivos(char *arq_entrada, char *arq_saida, char *comp)
{
    strcpy(arq_entrada, "entrada_");
    strcat(arq_entrada, comp);
    strcat(arq_entrada, ".txt");

    strcpy(arq_saida, "saida_");
    strcat(arq_saida, comp);
    strcat(arq_saida, ".txt");
}

int ler_valor(FILE *entrada)
{
    int valor;
    fscanf(entrada, "%d", &valor);
    return valor;
}

void main(int argc, char **argv)
{
    noArvore *raiz = NULL;

    char arq_entrada[14];
    char arq_saida[12];
    gera_nomes_arquivos(arq_entrada, arq_saida, argv[1]);
    FILE *entrada = fopen(arq_entrada, "r");

    int resposta = 1;
    while (resposta != 0)
    {
        resposta = ler_valor(entrada);

        if (resposta == 0)
        {
            // sair
            desalocaArvore(raiz);
            fclose(entrada);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            int valor = ler_valor(entrada);

            // busca antes para evitar inserir valor já existente
            if (busca(raiz, valor) == NULL)
            {
                noArvore *novo_no = alocaNo(valor);
                raiz = insere(raiz, novo_no);
            }
        }
        else if (resposta == 2)
        {
            int valor = ler_valor(entrada);
            raiz = removeNo(raiz, valor);
        }
        else if (resposta == 3)
        {
            // imprimir em pre-ordem
            imprimePreOrdem(raiz, arq_saida);
            FILE *saida = fopen(arq_saida, "a");
            fprintf(saida, "\n");
            fclose(saida);
        }
    }
}

