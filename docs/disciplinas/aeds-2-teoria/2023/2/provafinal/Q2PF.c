#include <stdio.h>
#include <stdlib.h>

/**
 * O presente algoritmo deve implementar
 * os seguintes métodos de uma estrutura
 * auto-ajustável:
 * Contador de frequência (CF)
 * Mover para frente (MF)
 * Transposição (TR)
*/

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
 * implemente a função a seguir
 */
void acessar_CF(no *ptlista, int chave)
{
    no *pointer = ptlista->prox, *ant = ptlista;;
    while (pointer != NULL)
    {
        if (pointer->chave == chave)
        {
            pointer->freq++;
            return;
        }
        pointer = pointer->prox;

        no *atual = ptlista->prox, *ant = ptlista;
        while(atual!=NULL && atual->freq <=pointer->freq){
            ant = atual;
            pointer = atual->prox;
        }
    
        pointer->prox = atual;
        ant->prox = pointer;
        return;
    }
    ant = pointer;
    pointer = pointer->prox;
}

/**
 * implemente a função a seguir
 */
void acessar_MF(no *ptlista, int chave)
{
    no *pointer = ptlista->prox;
    no *ant = ptlista;

    while (pointer != NULL)
    {
        if (pointer->chave == chave)
        {
            ant->prox = pointer->prox;
            pointer->prox = ptlista->prox;
            ptlista->prox = pointer;
            return;
        }
        ant = pointer;
        pointer = pointer->prox;
    }
}

/**
 * implemente a função a seguir
 */
void acessar_TR(no *ptlista, int chave)
{
    no *pointer = ptlista->prox;
    no *ant = ptlista;

    while (pointer != NULL && pointer->prox != NULL)
    {
        if (pointer->chave == chave)
        {
            no *proximo = pointer->prox;
            pointer->prox = proximo->prox;
            proximo->prox = pointer;
            ant->prox = proximo;
            return;
        }
        ant = pointer;
        pointer = pointer->prox;
    }
}

void imprimir(no *ptlista)
{
    if (ptlista->prox == NULL)
    {
        printf("<lista vazia!>");
        return;
    }

    ptlista = ptlista->prox;
    while (ptlista != NULL)
    {
        printf("%d:%d", ptlista->chave, ptlista->freq);
        ptlista = ptlista->prox;
        printf(" -> ");
        if (ptlista == NULL)
            printf("NULL");
    }
}

void desalocar_lista(no *ptlista)
{
    no *no_prox = ptlista->prox;
    while (no_prox != NULL)
    {
        no *no_temp = no_prox->prox;
        printf("desalocando nó: %d\n", no_prox->chave);
        free(no_prox);
        no_prox = no_temp;
    }
    printf("desalocando no cabeça\n");
    free(ptlista);
}

void ler_menu(int *resposta)
{
    printf("\n-----------------------\n");
    printf("escolha uma das opções:\n");
    printf("0 - sair\n");
    printf("1 - inserir\n");
    printf("2 - remover\n");
    printf("3 - acessar\n");
    printf("4 - imprimir\n");
    scanf("%d", resposta);
    printf("-----------------------\n\n");
}

void ler_menu_acesso(int *resposta)
{
    printf("\n-----------------------\n");
    printf("escolha o metodo de acesso:\n");
    printf("0 - Mover para frente (MF)\n");
    printf("1 - Transposição (TR)\n");
    printf("2 - Contador de frequência (CF)\n");
    scanf("%d", resposta);
    printf("-----------------------\n\n");
}

no *alocar_no()
{
    no *novo_no = malloc(sizeof(no));
    printf("informe a chave: ");
    scanf("%d", &(*novo_no).chave);
    printf("\n");
    novo_no->freq = 1;
    novo_no->prox = NULL;
    return novo_no;
}

void main()
{
    no *ptlista;
    ptlista = malloc(sizeof(no));
    ptlista->prox = NULL;

    int resposta;

    while (1)
    {
        ler_menu(&resposta);
        if (resposta == 0)
        {
            // sair
            desalocar_lista(ptlista);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            no *novo_no = alocar_no();
            if (inserir(ptlista, novo_no) == NULL)
            {
                printf("elemento inserido\n");
            }
            else
            {
                free(novo_no);
                printf("nó já existente na lista\n");
            }
        }
        else if (resposta == 2)
        {
            // remover
            int chave;
            printf("informe a chave do nó a ser removido: ");
            scanf("%d", &chave);
            no *no_removido = remover(ptlista, chave);
            if (no_removido != NULL)
            {
                printf("nó removido\n");
                printf("chave: %d\n", no_removido->chave);
                printf("frequência: %d\n", no_removido->freq);
                free(no_removido);
            }
            else
            {
                printf("nó inexistente\n");
            }
        }
        else if (resposta == 3)
        {
            // acessar
            int chave;
            printf("informe a chave do nó a ser acessado: ");
            scanf("%d", &chave);

            ler_menu_acesso(&resposta);
            if (resposta == 0)
            {
                acessar_MF(ptlista, chave);
                printf("MF\n");
            }
            else if (resposta == 1)
            {
                acessar_TR(ptlista, chave);
                printf("TR\n");
            }
            else if (resposta == 2)
            {
                acessar_CF(ptlista, chave);
                printf("CF\n");
            }
            else
            {
                printf("Opção inválida\n");
            }
        }
        else if (resposta == 4)
        {
            // imprimir
            imprimir(ptlista);
        }
        else
        {
            printf("Opção inválida\n");
        }
    }
}