#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * O objetivo do programa é funcionar como uma fila circular de alocação sequencial.
 * As funções de inserir e remover foram deixadas incompletas, e é seu trabalho é completá-las
 * de modo que o programa funcione da maneira esperada.
 *
 * Importante: ao executar o programa compilado você deve utilizar-se do script executar.sh.
 * Exemplo: supondo que você tenha compilado o código fonte da seguinte forma:
 * gcc Q3.c -o Q3
 *
 * Você deve chamar o script da seguinte forma:
 * ./executar.sh Q3
 *
 * Ou seja, o nome do executável gerado deve ser passado como argumento para o script.
 * Neste caso, Q3.
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
 * Complete a função a seguir, capaz de realizar a inserção.
 * Ela deve retornar uma das seguintes opções:
 *  - cenário de inserção:
 *      --> retorna a posição em que foi inserido
 *  - cenário fila cheia:
 *      --> retorna -1
 *
 * Sua função deve ter no máximo 8 ; (ponto e vírgula).
 */

int inserir(no F[], int *f, int *r, int M, no d)
{
    int aux = (*r + 1) % (M + 1);

    if (aux != *f) {
        *r = aux;
        F[*r].chave = d.chave;
        F[*r].valor = d.valor;
        if (*f == -1) {
            *f = *r;
        }
        return *r;
    }
    return -1;
}

/**
 * Complete a função a seguir, capaz de realizar a remoção.
 * Ela deve retornar uma das seguintes opções:
 *  - cenário de remoção:
 *      --> retorna o endereço para o nó
 *  - cenário de fila vazia:
 *      --> NULL
 *
 * Sua função deve ter no máximo 8 ; (ponto e vírgula).
 */

no *remover(no F[], int *f, int *r, int M)
{
    no *retorno = NULL;

    if (*f != -1)
    {
        retorno = malloc(sizeof(no));
        (*retorno).chave = F[*f].chave;
        (*retorno).valor = F[*f].valor;

        //*f = *f - 1;
    }

    return retorno;
}

void imprimir(no F[], int f, int r, int M, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");

    if (f == -1)
    {
        fprintf(saida, "<fila vazia!>");
    }
    else
    {
        fprintf(saida, "f-> ");
        while (f != r)
        {
            fprintf(saida, "%d:%d", F[f].chave, F[f].valor);
            f = (f + 1) % M;
            fprintf(saida, " | ");
        }
        fprintf(saida, "r-> %d:%d", F[f].chave, F[f].valor);
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

    int M = ler_valor(entrada);
    int resposta = 1;
    int f = -1, r = -1;

    no F[M];

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
            inserir(F, &f, &r, M, novo_no);
        }
        else if (resposta == 2)
        {
            // remover
            no *no_removido = remover(F, &f, &r, M);
            if (no_removido != NULL)
            {
                free(no_removido);
            }
        }
        else if (resposta == 3)
        {
            // imprimir
            imprimir(F, f, r, M, arq_saida);
        }
    }
}
