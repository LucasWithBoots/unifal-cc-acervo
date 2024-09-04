#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * O objetivo do programa é manipular uma lista com alocação sequencial
 * cujos valores serão inseridos em ordem crescente.
 * A função de busca binária foi deixada incompleta, e é seu trabalho é completá-la
 * de modo que o programa funcione da maneira esperada.
 * Todas as entradas de dados realizam as inserções já em ordem crescente, de modo
 * que a busca binária possa funcionar sem problemas.
 * Ou seja, você deve assumir que o vetor a ser recebido pela função de busca binária
 * terá sempre os números já previamente ordenados em ordem crescente.
 *
 * Importante: ao executar o programa compilado você deve utilizar-se do script executar.sh.
 * Exemplo: supondo que você tenha compilado o código fonte da seguinte forma:
 * gcc Q2.c -o Q2
 *
 * Você deve chamar o script da seguinte forma:
 * ./executar.sh Q2
 *
 * Ou seja, o nome do executável gerado deve ser passado como argumento para o script.
 * Neste caso, Q2.
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

typedef struct no_
{
    int chave;
    int valor;
} no;

/**
 * Complete a função a seguir, capaz de realizar a busca binária.
 * Ela deve retornar uma das seguintes opções:
 *  - cenário de inserção:
 *    -> caso a chave passada não esteja presente na lista:
 *          --> retorna -1
 *  - cenário de não inserção:
 *    -> caso a chave passada esteja presente na lista:
 *          --> retorna o índice do elemento que contém a chave
 *
 * Sua função deve ter no máximo 8 ; (ponto e vírgula).
 */

int busca_bin(no L[], int n, int x)
{
    int inf = 0, sup = n - 1; 
    int conta = 0;
    while(conta < (n/2)+1){
        int meio = ((inf + sup)/2);
        if (L[meio].chave > x){
            sup  = meio;
        }else if(L[meio].chave < x){ 
            inf = meio;
        }else{
            return meio;
        }
        conta++;
    }
    return -1;
}

int inserir(no L[], int n, int m, no d)
{
    if (n < m)
    {
        if (busca_bin(L, n, d.chave) == -1)
        {
            L[n].chave = d.chave;
            L[n].valor = d.valor;
            return n + 1;
        }
        return 0;
    }
    return -1;
}

no *remover(int x, no L[], int *n)
{
    no *retorno = NULL;
    if (n != 0)
    {
        int indice = busca_bin(L, *n, x);
        if (indice >= 0)
        {
            retorno = malloc(sizeof(no));
            (*retorno).chave = L[indice].chave;
            (*retorno).valor = L[indice].valor;

            for (int i = indice; i < (*n) - 1; i++)
            {
                L[i].chave = L[i + 1].chave;
                L[i].valor = L[i + 1].valor;
            }
            *n = (*n) - 1;
        }
    }

    return retorno;
}

void imprimir(no L[], int n, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");
    if (!n)
    {
        fprintf(saida, "<lista vazia!>");
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(saida, "%d:%d", L[i].chave, L[i].valor);
        if (i < n - 1)
            fprintf(saida, " | ");
    }
    fprintf(saida, "\n");
    fclose(saida);
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
    char arq_entrada[14];
    char arq_saida[12];
    gera_nomes_arquivos(arq_entrada, arq_saida, argv[1]);
    FILE *entrada = fopen(arq_entrada, "r");

    int m = ler_valor(entrada);
    int n = 0;
    int resposta = 1;

    no L[m];

    while (resposta != 0)
    {
        resposta = ler_valor(entrada);

        if (resposta == 0)
        {
            // sair
            fclose(entrada);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            no novo_no;
            novo_no.chave = ler_valor(entrada);
            novo_no.valor = ler_valor(entrada);

            int valor_retornado = inserir(L, n, m, novo_no);
            if (valor_retornado > 0)
            {
                n = valor_retornado;
            }
        }
        else if (resposta == 2)
        {
            // remover
            int chave = ler_valor(entrada);

            no* no_removido = remover(chave, L, &n);
            if(no_removido != NULL){
                free(no_removido);
            }
        }
        else if (resposta == 3)
        {
            // imprimir
            imprimir(L, n, arq_saida);
        }
    }
}
