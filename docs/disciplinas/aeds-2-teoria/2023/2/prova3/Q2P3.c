#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Valor: 4,0 pontos */

/**
 * O presente código tem por objetivo
 * funcionar como uma lista (com alocação encadeada)
 * que se auto ajuste ao se acessar um elemento da lista
 * de acordo com o método Contador de Frequência (CF).
 * 
 * Seu objetivo é completar a função acessar_CF de modo que
 * o código funcione corretamente.
*/

//Struct da estrutura do nó
typedef struct no_
{
    int chave;
    int freq;
    struct no_ *prox;
} no;

/**
 * Retorna o endereço do nó caso ele já exista
 * (caso em que a inserção não foi realizada),
 * ou NULL em caso de inserção bem sucedida.
 */
no *inserir(no *ptlista, no *novo_no)
{
    no *ptr = ptlista->prox;
    no *ant = ptlista;
    while (ptr != NULL)
    {
        if (ptr->chave == novo_no->chave)
            return ptr;
        ant = ptr;
        ptr = ptr->prox;
    }

    ant->prox = novo_no;

    return NULL;
}

/**
 * Retorna o endereço do nó removido,
 * ou NULL em caso de não encontrado.
 */

no *remover(no *ptlista, int chave)
{
    no *ptr = ptlista->prox;
    no *ant = ptlista;
    while (ptr != NULL)
    {
        if (ptr->chave == chave)
        {
            ant->prox = ptr->prox;
            return ptr;
        }
        ant = ptr;
        ptr = ptr->prox;
    }

    return NULL;
}

/**
 * Implemente a função a seguir de modo que 
 * a lista funcione de acordo com o método
 * Contador de Frequência (CF).
 * Definição do método CF:
 * Cada nó possui um contador, onde é mantido
 * o número de acessos efetuados.
 * Após cada acesso, o contador é incrementado,
 * e esse nó é movido para uma posição tal que 
 * todos os nós com contador menor estejam
 * situados depois dele.
 * 
 * Exemplo:
 * estado inicial (nó.frequência): a.8, b.5, c.5, w.4, y.3, z.3, f.3, x.3
 *  --> acesso a x
 * estado final: a.8, b.5, c.5, w.4, x.4, y.3, z.3, f.3
 * 
 * Limitação do problema: use no máximo 12;
*/

void acessar_CF(no *ptlista, int chave)
{
    no *ptr = ptlista->prox;
    no *ant = ptlista;
    no *prev = ptlista;
    no *prev_ant = ptlista;
    while (ptr != NULL)
    {
        if (ptr->chave == chave)
        {
            ptr->freq++;
            while (prev->prox != ptr && prev->prox->freq <= ptr->freq)
            {
                prev_ant = prev;
                prev = prev->prox;
            }
            if (prev->prox != ptr)
            {
                ant->prox = ptr->prox;
                if (prev == ptlista) {
                    ptlista->prox = ptr;
                } else {
                    prev_ant->prox = ptr;
                }
                ptr->prox = prev;
            }
            return;
        }
        ant = ptr;
        ptr = ptr->prox;
    }
    return;
}
void imprimir(no *ptlista, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");
    if (ptlista->prox == NULL)
    {
        fprintf(saida, "<lista vazia!>");
        return;
    }

    ptlista = ptlista->prox;
    while (ptlista != NULL)
    {
        fprintf(saida, "%d:%d", ptlista->chave, ptlista->freq);
        ptlista = ptlista->prox;
        fprintf(saida, " -> ");
        if (ptlista == NULL)
            fprintf(saida, "NULL\n");
    }
    fclose(saida);
}

void desalocar_lista(no *ptlista)
{
    no *no_prox = ptlista->prox;
    while (no_prox != NULL)
    {
        no *no_temp = no_prox->prox;
        free(no_prox);
        no_prox = no_temp;
    }
    free(ptlista);
}

no *alocar_no(int chave)
{
    no *novo_no = malloc(sizeof(no));
    novo_no->chave = chave;
    novo_no->freq = 1;
    novo_no->prox = NULL;
    return novo_no;
}

int ler_valor(FILE *entrada)
{
    int valor;
    fscanf(entrada, "%d", &valor);
    return valor;
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

void main(int argc, char **argv)
{
    char arq_entrada[14];
    char arq_saida[12];
    gera_nomes_arquivos(arq_entrada, arq_saida, argv[1]);
    FILE *entrada = fopen(arq_entrada, "r");

    no *ptlista;
    ptlista = malloc(sizeof(no));
    ptlista->prox = NULL;

    int resposta = 1;

    while (resposta != 0)
    {
        resposta = ler_valor(entrada);
        if (resposta == 0)
        {
            // sair
            desalocar_lista(ptlista);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            no *novo_no = alocar_no(ler_valor(entrada));
            if (inserir(ptlista, novo_no) != NULL)
            {
                free(novo_no);
            }
        }
        else if (resposta == 2)
        {
            // remover
            no *no_removido = remover(ptlista, ler_valor(entrada));
            if (no_removido != NULL)
            {
                free(no_removido);
            }
        }
        else if (resposta == 3)
        {
            // acessar
            acessar_CF(ptlista, ler_valor(entrada));
        }
        else if (resposta == 4)
        {
            // imprimir
            imprimir(ptlista, arq_saida);
        }
    }
}
