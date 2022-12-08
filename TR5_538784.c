#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/*Definicao do tipo de funcao a ser utilizado para comparacao
Esta funcao recebe dois valores x e y e retorna

1 : se x menor que y.
0 : se x equivalente a y.
-1: se x maior que y na ordem.

*/
typedef int COMP(void* x, void* y);

//Uma Heap estatico. Os elementos do vetor estao colocadoo no vetor
//de acordo com a ordem indicada por comparador.
typedef struct heap{
	int N;//tamanho do vetor
	int P;//numero de elementos no vetor
	void** elems;//o vetor de elementos
	COMP* comparador;//a funcao de comparacao
}HEAP;

/**
Cria um heap vazio de tamanho n e com funcao de comparacao compara

parametro n: o tamanho do heap
parametro compara: a funcao de comparacao

o retorno é um ponteiro para uma estrutura HEAP, observe que este ponteiro ja
deve apontar para a estrutura, ou seja, a alocacao de memoria deve ser feita nele.
*/
HEAP* HEAP_create(int n, COMP* compara) {
	HEAP* heap = malloc(sizeof(HEAP));
	heap->elems = malloc(n * sizeof(void*));
	heap->N = n;
	heap->P = 0;
	heap->comparador = compara;

	return heap;
}

/**
Adiciona o elemento newelem ao Heap, na posicao correta se for possÃ­vel
ainda incluir o elemento (se existe espaco no vetor elems). Observe que 
a estrutura deve respeitar a regra da heap, ou seja, para todo i temos que 
x[i] menor que ou equivalente a x[2*i] e a x[2*i+1].

parametro heap: o heap a ter o elemento incluido
parametro newelem: o elemento a ser adicionado
*/
void HEAP_add(HEAP* heap, void* newelem) {
  if (heap->P < heap->N) {
    heap->elems[heap->P] = newelem;
	int pos = heap->P;

	while (heap->comparador(heap->elems[pos], heap->elems[(pos - 1) / 2]) > 0) {
		void* aux = heap->elems[pos];
		heap->elems[pos] = heap->elems[(pos - 1) / 2];
		heap->elems[(pos - 1) / 2] = aux;	
		pos = (pos - 1) / 2;
	}	

	heap->P++;
  }
}

/**
Remove o menor elemento do heap, de acordo com a funcao compara

parametro heap: o heap a ter seu elemento removido

o retorno é um ponteiro para o elemento que foi removido do heap.
*/
void* HEAP_remove(HEAP* heap) {
	void* min = heap->elems[0];

	heap->elems[0] = heap->elems[heap->P - 1];
	heap->elems[heap->P - 1] = min;
	
	heap->P--;

	int pai = 0;
	int filho = pai * 2 + 1;
	
	while (filho < heap->P) {
		if (filho + 1 < heap->P) {
			if (heap->comparador(heap->elems[filho], heap->elems[filho + 1]) < 0) {
				filho += 1;
			}
		}

		if (heap->comparador(heap->elems[pai], heap->elems[filho]) < 0) {
			void* aux = heap->elems[pai];
			heap->elems[pai] = heap->elems[filho];
			heap->elems[filho] = aux;

			pai = filho;
			filho = pai * 2 + 1;
		} else {
			filho = heap->P + 1;
		}
	}

	return min;
}

