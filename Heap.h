#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <stdlib.h>

typedef struct Heap Heap;

Heap* criaHeap(size_t tam, size_t bytes, int (*compar)(void*a, void*b));

void pushH(Heap* h, void* x); //----// Dá push em um objeto na fila de prioridade.

void* topH(Heap* h, void* storage); // Retorna o topo da fila (o objeto com maior prioridade).

void popH(Heap* h); //--------------// Dá pop em um objeto na fila de prioridade.

void* clearH(Heap* h); //-----------// Recebe uma fila de prioridade, e a apaga.

int fullH(Heap* h); //--------------// Retorna 1 se estiver cheio, 0 caso contrário.

int emptyH(Heap* h); //-------------// Retorna 1 se estiver vazio, 0 caso contrário.

// As funções siftUpH, siftDownH e trocaH são da implementação.


#endif // HEAP_H_INCLUDED
