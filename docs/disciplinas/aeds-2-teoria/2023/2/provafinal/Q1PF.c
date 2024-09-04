/*
 * Este algoritmo implementa o funcionamento de 
 * uma árvore binária de busca. O seu objetivo
 * é implementar duas funções complementares
 * no algoritmo:
 *  - estritamente_binaria
 *  - balanceada
 * 
 * as descrições de ambas estão disponíveis
 * no próprio código.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct noArvore_ noArvore;

struct noArvore_
{
	int valor;
	noArvore *esq;
	noArvore *dir;
};

/**
 *
 * @param valor valor a ser atribuido no no
 * @return no criado
 */
noArvore *cria_no(int valor)
{
	noArvore *n = malloc(sizeof(noArvore));
	n->valor = valor;
	n->esq = NULL;
	n->dir = NULL;

	return n;
}

/**
 *
 * @param raiz da arvore a ser desalocada
 */
void desaloca_arvore(noArvore *raiz)
{
	if (raiz != NULL)
	{
		desaloca_arvore(raiz->esq);
		desaloca_arvore(raiz->dir);

		free(raiz);
	}
}

/**
 *
 * @param raiz
 * @param n no a ser inserido na arvore
 * @return raiz da arvore
 */
noArvore *insere(noArvore *raiz, noArvore *n)
{
	if (raiz == NULL)
		return n;

	if (raiz->valor > n->valor)
		raiz->esq = insere(raiz->esq, n);
	else if (raiz->valor < n->valor)
		raiz->dir = insere(raiz->dir, n);

	return raiz;
}

/**
 *
 * @param raiz a ser removida
 * @return a arvore apos a raiz ter sido removida
 */
noArvore *removeRaiz(noArvore *raiz)
{

	noArvore *p, *q;

	/*
	 * caso a raiz nao tenha sub-arvore esqueda,
	 * a remocao consiste em tornar o no a direita
	 * a nova raiz
	 */
	if (raiz->esq == NULL)
	{
		q = raiz->dir;
		free(raiz);
		return q;
	}

	/*
	 * caso tenha sub-arvore esquerda, encontrar dentro da sub-arvore
	 * esquerda o no mais a direita, que e o no que precede a raiz em
	 * valor
	 */
	p = raiz;
	q = raiz->esq;
	while (q->dir != NULL)
	{
		p = q;
		q = q->dir;
	}

	/*
	 * se o no da sub-arvore esquerda tiver ao menos um
	 * filho a direita, essa condicao sera verdadeira
	 */
	if (raiz != p)
	{
		p->dir = q->esq;
		/*
		 * atualizando para que o ponteiro esq do no q, que sera a nova raiz,
		 * passe a apontar para a sub-arvore esquerda da raiz a ser removida
		 */
		q->esq = raiz->esq;
	}

	/*
	 * atualizando para que o ponteiro dir do no q, que sera a nova raiz,
	 * passe a apontar para a sub-arvore direita da raiz a ser removida
	 */
	q->dir = raiz->dir;

	/*
	 * desalocando a raiz
	 */
	free(raiz);

	return q;
}

/**
 *
 * @param raiz
 * @param valor
 * @return o no caso tenha sido encontrado
 */
noArvore *buscaNo(noArvore *raiz, int valor)
{
	if (raiz == NULL)
		return NULL;

	if (raiz->valor == valor)
		return raiz;

	if (raiz->valor > valor)
		return buscaNo(raiz->esq, valor);
	else
		return buscaNo(raiz->dir, valor);
}

/**
 *
 * @param raiz
 * @param no
 * @return o pai do no, caso exista ou nulo caso o no seja a raiz.
 */
noArvore *buscaPai(noArvore *raiz, noArvore *no)
{
	if (raiz == no)
	{
		return NULL;
	}

	if (raiz->dir == no || raiz->esq == no)
	{
		return raiz;
	}

	if (raiz->valor > no->valor)
	{
		return buscaPai(raiz->esq, no);
	}
	else
	{
		return buscaPai(raiz->dir, no);
	}
}

/**
 *
 * @param raiz
 * @param valor
 * @return a raiz da arvore apos o no ter sido removido
 */
noArvore *removeNo(noArvore *raiz, int valor)
{
	noArvore *no = buscaNo(raiz, valor);
	if (no)
	{
		noArvore *pai = buscaPai(raiz, no);
		if (pai)
		{
			if (pai->dir == no)
			{
				pai->dir = removeRaiz(no);
			}
			else
			{
				pai->esq = removeRaiz(no);
			}
		}
		else
		{
			raiz = removeRaiz(no);
		}
	}

	return raiz;
}

void pre_ordem(noArvore *raiz)
{
	if (raiz != NULL)
	{
		printf("%d ", raiz->valor);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void em_ordem(noArvore *raiz)
{
	if (raiz != NULL)
	{
		em_ordem(raiz->esq);
		printf("%d ", raiz->valor);
		em_ordem(raiz->dir);
	}
}

void pos_ordem(noArvore *raiz)
{
	if (raiz != NULL)
	{
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d ", raiz->valor);
	}
}

/**
 * Uma árvore binária de busca é estritamente
 * binária se todos os nós da árvore tem 0 ou 2 filhos.
 * Implemente a função a seguir, que deve
 * escrever 'verdadeiro' caso a árvore seja
 * estritamente binária, e 'falso' caso
 * contrário.
 */
int estritamente_binaria(noArvore *raiz)
{   
    if(raiz==NULL){
        printf("Arvore vazia, binária");
        return 1;
    }

    if((raiz->esq==NULL && raiz->dir!=NULL)||(raiz->esq!=NULL&&raiz->dir==NULL)){
        printf("false\n");
        return 0;
    }

    if(raiz->esq!=NULL && raiz->dir != NULL){
        int esq = estritamente_binaria(raiz->esq);
        int dir = estritamente_binaria(raiz->dir);
        if(esq && dir){
            printf("verdadeiro\n");
            return 1;
        }else{
            printf("falso\n");
            return 0;
        }
    }
    
    printf("verdadeiro\n");
    return 1;
}

/**
 * A função a seguir deve escrever
 * 'verdadeiro' caso a árvore esteja balanceada
 * (utilizando-se o critério da AVL),
 * e 'falso' caso contrário.
 */
void balanceada(noArvore *raiz)
{
	if(raiz==NULL){
		printf("verdadeiro\n");
		return;
	}

	if((raiz->esq == NULL && raiz->dir!=NULL &&(raiz->dir->esq!=NULL||raiz->dir->dir!=NULL))){
		printf("false");
		return;
	}
	balanceada(raiz->esq);
	balanceada(raiz->dir);
}

void ler_menu(int *resposta)
{
	printf("\n-----------------------\n");
	printf("escolha uma das opções:\n");
	printf("0 - sair\n");
	printf("1 - inserir\n");
	printf("2 - remover\n");
	printf("3 - pre ordem\n");
	printf("4 - em ordem\n");
	printf("5 - pos ordem\n");
	printf("6 - estritamente binaria?\n");
	printf("7 - balanceada?\n");
	scanf("%d", resposta);
	printf("-----------------------\n\n");
}

int main()
{

	noArvore *raiz = NULL;
	noArvore *n;

	int resposta = 1;
	int valor;

	while (resposta != 0)
	{

		ler_menu(&resposta);

		switch (resposta)
		{
		case 0:
			break;
		case 1:
			printf("informe o valor a inserir: ");
			scanf("%d", &valor);
			n = cria_no(valor);
			raiz = insere(raiz, n);
			pre_ordem(raiz);
			break;
		case 2:
			printf("informe o valor a remover: ");
			scanf("%d", &valor);
			raiz = removeNo(raiz, valor);
			break;
		case 3:
			pre_ordem(raiz);
			break;
		case 4:
			em_ordem(raiz);
			break;
		case 5:
			pos_ordem(raiz);
			break;
		case 6:
			estritamente_binaria(raiz);
			break;
		case 7:
			balanceada(raiz);
			break;
		default:
			printf("opcao invalida\n");
		}
	}

	desaloca_arvore(raiz);

	return (EXIT_SUCCESS);
}