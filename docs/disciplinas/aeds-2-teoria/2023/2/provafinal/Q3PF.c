#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_INICIAL 100

/**
 * Imagine que você esteja desenvolvendo em uma
 * versão pouco convencional da linguagem C,
 * onde o índice de vetor comece no número 7.
 * 
 * Neste caso, por exemplo, caso o usuário declarasse
 * um vetor contendo 5 posições, os seus índices seriam
 * os seguintes:
 * 
 *  [7]  [8]  [9]  [10] [11]
 * |    |    |    |    |    |
 * 
 * Infelizmente(?) nós não temos tal versão de linguagem,
 * mas podemos simular tal comportamento, de modo a nunca
 * usarmos posições inferiores a 7.
 * 
 * Por exemplo, caso desejemos um vetor com 5 posições,
 * nada nos impede de declararmos o vetor como tendo 
 * tamanho igual a 12, de modo a somente usarmos os
 * índices de 7 a 11, deixando os índices anteriores
 * a 7 vazios.
 * 
 * A seguir temos uma ilustração de tal cenário:
 * 
 *  [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7]  [8]  [9]  [10] [11]
 * |VAZIO|VAZIO|VAZIO|VAZIO|VAZIO|VAZIO|VAZIO|    |    |    |    |    |
 * 
 * No presente exercício o objetivo é você desenvolver
 * uma Heap que ofereça o menor valor na posição 
 * inicial do vetor (no caso, a posição 7). A partir da
 * posição inicial, o funcionamento é conforme 
 * se espera para uma Heap.
 * 
 * O tamanho do vetor é limitado a 100 posições, podendo a Heap
 * ter portanto, até 93 elementos.
*/

//considere o indice inicial diferente, de acordo com seu nome:
// - Nycole - o vetor inicia na posicao 7.
// - Gustavo - o vetor inicia na posicao 8.
// - Jose Olavo - o vetor inicia na posicao 9.
// - Luis Filipi - o vetor inicia na posicao 10.
// - Rikson - o vetor inicia na posicao 11.

typedef struct heap_ {
    int * valores;
    int pos;
    int tamanho;
}heap;

void inicia_heap(heap * min_heap){
    min_heap->pos = 7; //<-- primeira posição da heap
    min_heap->tamanho = TAMANHO_INICIAL;
    min_heap->valores = malloc(TAMANHO_INICIAL * sizeof(int));
}

void print(heap* min_heap){
    int i;
    for(i = 7; i < min_heap->pos; i++){
        printf("%d ", min_heap->valores[i]);
    }
    printf("\n\n");
}

/**
 * Complete as linhas que faltam!
 * Fique atento aos limites de ;.
*/

int insere_heap(heap * min_heap, int valor){
    
    min_heap->valores[min_heap->pos] = valor;
    int pos = min_heap->pos;

    //ajusta a posição do elemento removido para manter as propriedades da heap
    while(pos > 7 && min_heap->valores[pos] < min_heap->valores[(pos - 1) / 2]){
        
        //troca o valor atual com o pai, se o valor for menor
        int tmp = min_heap->valores[pos];

        min_heap->valores[pos] = min_heap->valores[(pos - 1) / 2];
        min_heap->valores[(pos - 1) / 2] = tmp;

        //aualiza a posição para a posição do pai
        pos = (pos - 1) / 2;
    }
    //incrementa a posição para a próxima inserção
    min_heap->pos++;

    return 0;
}

int *remove_heap(heap *min_heap){

    int *valor_retorno = NULL;
    
    if(min_heap->pos == 7){
        return valor_retorno;
    }

    valor_retorno = malloc(sizeof(int));

    //armazena o valor mínimo, que está na posição inicial da Heap (posição 7)
    *valor_retorno = min_heap->valores[7];

    //substitui o valor removido pelo último valor na Heap
    min_heap->valores[7] = min_heap->valores[min_heap->pos - 1];
    min_heap->pos--;

    //Inicia a posição para ajustar o elemento removido e manter as propriedades da Heap
    int pos = 7;

    //ajusta a posição do elemento removido para manter as propriedades da heap
    while(2 * pos + 1 < min_heap->pos){
        int filho_esq = 2 * pos + 1;
        int filho_dir = 2 * pos + 2;
        int menor_filho = filho_esq;

        //encontra o menor dos dois filhos 
        if(filho_dir < min_heap->pos && min_heap->valores[filho_dir] < min_heap->valores[filho_esq]){
            menor_filho = filho_dir;
        }

        //troca com o menor filho, se necessário 
        if(min_heap->valores[pos] > min_heap->valores[menor_filho]){
            int tmp = min_heap->valores[pos];
            min_heap->valores[pos] = min_heap->valores[menor_filho];
            min_heap->valores[menor_filho] = tmp;
            pos = menor_filho;//atualiza a posição para próxima intereção
        } else {
            break;
        }
    }

    return valor_retorno;
}

int main(){
    heap min_heap;
    inicia_heap(&min_heap);

    int ans = 1;
    int valor;
    int *removido;
    while(ans){
        printf("1 - inserir\n");
        printf("2 - remover\n");
        printf("3 - imprimir\n");
        printf("0 - sair\n");
        scanf("%d", &ans);

        switch(ans){
            case 0:
                printf("saindo...");
                break;
            case 1:
                printf("valor a ser inserido: ");
                scanf("%d", &valor);
                if(insere_heap(&min_heap, valor) == 1){
                    printf("erro ao inserir\n");
                }
                break;
            case 2:
                removido = remove_heap(&min_heap);
                if(removido == NULL){
                    printf("heap vazia\n");
                }else{
                    printf("valor removido: %d\n", *removido);
                }
                break;
            case 3:
                print(&min_heap);
                break;
            default:
                printf("opcao invalida\n");
        }
    }

    return 0;
}