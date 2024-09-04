#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Valor: 3,0 pontos */

/**
 * O presente código tem por objetivo
 * funcionar como uma lista (com alocação sequencial)
 * que se auto ajuste ao se acessar um elemento da lista
 * de acordo com o método Mover para a Frente (MF).
 * 
 * Seu objetivo é completar a função acessar_MF de modo que
 * o código funcione corretamente.
*/

//Struct representando um nó
typedef struct no_
{
    int chave;
    int frequencia;
} no;

//Struct para a manipulação da lista
typedef struct lista_
{
    //lista em si
    no *estrutura;
    //tamanho máximo
    int tam_max;
    //quantidade atual de elementos na lista
    int qt_elementos;
} lista;

void inserir(lista *l, int chave)
{
    if (l->qt_elementos + 1 <= l->tam_max)
    {
        l->estrutura[l->qt_elementos].chave = chave;
        l->estrutura[l->qt_elementos].frequencia = 1;
        l->qt_elementos++;
    }
}

void remover(lista *l, int chave)
{
    int i = 0;
    while (i < l->qt_elementos && l->estrutura[i].chave != chave)
    {
        i++;
    }
    if (i < l->qt_elementos)
    {
        for (; i < l->qt_elementos - 1; i++)
        {
            l->estrutura[i].chave = l->estrutura[i + 1].chave;
            l->estrutura[i].frequencia = l->estrutura[i + 1].frequencia;
        }
        l->qt_elementos--;
    }
}

/**
 * Implemente a função a seguir de modo que 
 * a lista funcione de acordo com o método
 * Mover para a Frente (MF).
 * Definição do método MF:
 * Neste método, quando a chave desejada é encontrada,
 * o nó é transferido para o início da lista.
 * Observe que a cada acesso o campo frequencia 
 * (contido dentro do nó) é incrementado de uma unidade.
 * 
 * Exemplo:
 * estado inicial (nó.frequencia): a.8, b.5, c.5, w.4, y.3, z.3, f.3, x.3
 *  --> acesso a x
 * estado final: x.4, a.8, b.5, c.5, w.4, y.3, z.3, f.3
 * 
 * Limitação do problema: use no máximo 8;
*/

void acessar_MF(lista *l, int chave)
{
    //TODO: seu código aqui :-)
    int i = 0; // variavel para percorrer a lista
    while (i < l->qt_elementos && l->estrutura[i].chave != chave)
    {
        i++; // percorre a lista até encontrar a chave
    }
    no aux; // variavel auxiliar para trocar os valores
    if (i < l->qt_elementos)
    {
        aux = l->estrutura[i]; // salva o valor do nó
        for (; i > 0; i--)
        {
            l->estrutura[i].chave = l->estrutura[i - 1].chave; // troca os valores
            l->estrutura[i].frequencia = l->estrutura[i - 1].frequencia; // troca os valores
        }
        l->estrutura[0] = aux; // salva o valor do nó
        l->estrutura[0].frequencia++; // incrementa a frequencia
    }
}

void imprimir(lista *l, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");
    for (int i = 0; i < l->qt_elementos; i++)
    {
        if (i < l->qt_elementos - 1)
            fprintf(saida, "|chave - %d: freq - %d| -> ", l->estrutura[i].chave, l->estrutura[i].frequencia);
        else
            fprintf(saida, "|chave - %d: freq - %d|\n", l->estrutura[i].chave, l->estrutura[i].frequencia);
    }
    fclose(saida);
}

/**
 * funcoes auxiliares, apenas para diminuir a quantidade de codigo na main
 **/

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

    int M = ler_valor(entrada);

    lista l;
    l.estrutura = malloc(M * sizeof(no));
    l.tam_max = M;
    l.qt_elementos = 0;

    int resposta = 1;
    while (resposta != 0)
    {
        resposta = ler_valor(entrada);

        if (resposta == 0)
        {
            // sair
            free(l.estrutura);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            int chave = ler_valor(entrada);
            inserir(&l, chave);
        }
        else if (resposta == 2)
        {
            // remover
            int chave = ler_valor(entrada);
            remover(&l, chave);
        }
        else if (resposta == 3)
        {
            // acessar
            int chave = ler_valor(entrada);
            acessar_MF(&l, chave);
        }
        else if (resposta == 4)
        {
            // imprimir
            imprimir(&l, arq_saida);
        }
    }
}
