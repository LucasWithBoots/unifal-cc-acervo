#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * O presente programa tem como objetivo implementar uma lista duplamente encadeada.
 * Algumas funções foram deixadas incompletas.
 * Seu trabalho é completá-las de modo que o programa funcione da maneira esperada.
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

typedef struct no_
{
    int chave;
    int valor;
    struct no_ *ant;
    struct no_ *prox;
} no;

no *buscar(no *ptlista, int x)
{
    no *ultimo = ptlista->ant;

    if (ultimo != ptlista && x <= ultimo->chave)
    {
        no *pont = ptlista->prox;
        while (pont->chave < x)
        {
            pont = pont->prox;
        }
        return pont;
    }
    return ptlista;
}

/**
 * Complete a função a seguir.
 * Ela deve retornar uma das seguintes opções:
 *  - caso ocorra a inserção:
 *      --> retorna NULL
 *  - caso não ocorra a inserção:
 *      --> retorna o endereço retornado pela função buscar
 *
 * Sua função deve ter no máximo 9 ; (ponto e vírgula).
 */
no *inserir(no *ptlista, no *novo_no)
{
    no *pont = buscar(ptlista, novo_no->chave);

    if(pont == ptlista || pont->chave != novo_no->chave){
        novo_no->prox = pont;
        novo_no->ant = pont->ant;
        pont->ant->prox = novo_no;
        pont->ant = novo_no;
        return NULL; 
        }
        
    return pont;
}

/**
 * Complete a função a seguir.
 * Ela deve retornar uma das seguintes opções:
 *  - caso ocorra a remoção:
 *      --> endereço do nó removido
 *  - caso não ocorra a remoção (nó não encontrado):
 *      --> NULL
 *
 * Sua função deve ter no máximo 7 ; (ponto e vírgula).
 */
no *remover(no *ptlista, int x)
{
    no *pont = buscar(ptlista, x);

    if(pont->chave == x && pont != ptlista){
        pont->ant->prox = pont->prox;
        pont->prox->ant = pont->ant;
        return pont;
    }


    return NULL;
}

void imprimir_crescente(no *ptlista, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");

    no *proximo = ptlista->prox;
    if (proximo == ptlista)
    {
        fprintf(saida, "<lista vazia!>");
    }
    else
    {
        while (proximo != ptlista)
        {
            fprintf(saida, "%d:%d", proximo->chave, proximo->valor);
            proximo = proximo->prox;
            if (proximo != ptlista)
                fprintf(saida, " -> ");
        }
    }
    fprintf(saida, "\n");
    fclose(saida);
}

void imprimir_decrescente(no *ptlista, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");

    no *anterior = ptlista->ant;
    if (anterior == ptlista)
    {
        fprintf(saida, "<lista vazia!>");
    }
    else
    {
        while (anterior != ptlista)
        {
            fprintf(saida, "%d:%d", anterior->chave, anterior->valor);
            anterior = anterior->ant;
            if (anterior != ptlista)
                fprintf(saida, " -> ");
        }
    }
    fprintf(saida, "\n");
    fclose(saida);
}

void desalocar_lista(no *ptlista)
{
    no *proximo = ptlista->prox;
    while (proximo != ptlista)
    {
        no *temp = proximo->prox;
        free(proximo);
        proximo = temp;
    }
    free(ptlista);
}

int ler_valor(FILE *entrada)
{
    int valor;
    fscanf(entrada, "%d", &valor);
    return valor;
}

no *alocar_no(int chave, int valor)
{
    no *novo_no = malloc(sizeof(no));
    novo_no->chave = chave;
    novo_no->valor = valor;
    novo_no->prox = NULL;
    novo_no->ant = NULL;
    return novo_no;
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

void inicia_lista(no **ptlista)
{
    *ptlista = malloc(sizeof(no));

    (*(*ptlista)).ant = (*ptlista);
    (*(*ptlista)).prox = (*ptlista);
}

void main(int argc, char **argv)
{
    no *ptlista;
    inicia_lista(&ptlista);

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
            desalocar_lista(ptlista);
            fclose(entrada);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            int chave = ler_valor(entrada);
            int valor = ler_valor(entrada);
            no *novo_no = alocar_no(chave, valor);
            if (inserir(ptlista, novo_no) != NULL)
            {
                free(novo_no);
            }
        }
        else if (resposta == 2)
        {
            // remover
            int chave = ler_valor(entrada);
            no *no_removido = remover(ptlista, chave);
            if (no_removido != NULL)
            {
                free(no_removido);
            }
        }
        else if (resposta == 3)
        {
            // imprimir ordem crescente
            imprimir_crescente(ptlista, arq_saida);
        }
        else if (resposta == 4)
        {
            // imprimir ordem decrescente
            imprimir_decrescente(ptlista, arq_saida);
        }
    }
}
