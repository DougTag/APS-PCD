#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <stdlib.h>

typedef struct Heap Heap;

Heap* criaHeap(size_t tam, size_t bytes, int (*compar)(void*a, void*b));

void pushH(Heap* h, void* x); //----// D� push em um objeto na fila de prioridade.

void* topH(Heap* h, void* storage); // Retorna o topo da fila (o objeto com maior prioridade).

void popH(Heap* h); //--------------// D� pop em um objeto na fila de prioridade.

void* clearH(Heap* h); //-----------// Recebe uma fila de prioridade, e a apaga.

int fullH(Heap* h); //--------------// Retorna 1 se estiver cheio, 0 caso contr�rio.

int emptyH(Heap* h); //-------------// Retorna 1 se estiver vazio, 0 caso contr�rio.

// As fun��es siftUpH, siftDownH e trocaH s�o da implementa��o.


#endif // HEAP_H_INCLUDED
