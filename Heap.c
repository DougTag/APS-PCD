#include "Heap.h"

#include <stdlib.h> //  malloc(), NULL, size_t
#include <string.h> //  memcpy()

struct Heap{
    void* _p; //------------------------// Ponteiro para o local da memória onde ficará a heap.
    size_t _maxTam; //------------------// Quantidade máxima de objetos na heap
    size_t _bytes; //-------------------// Tamanho em bytes objeto colocado na heap
    size_t _fim; //---------------------// Posição do último elemento da heap.

    int (*_compar)(void* a, void* b); //// Função que determina a prioridade entre dois objetos. Deve retornar:
                                      // *  -> Valor positivo, se (a) tem maior prioridade que (b);
                                      // *  -> Valor negativo ou 0, caso contrário.
                                      // * Note que essa implementação não garante estabilidade.
};

void trocaH(Heap* h, size_t pos1, size_t pos2){
    char aux[h->_bytes];
    memcpy(aux, &h->_p[h->_bytes*pos1], h->_bytes);
    memcpy(&h->_p[h->_bytes*pos1], &h->_p[h->_bytes*pos2], h->_bytes);
    memcpy(&h->_p[h->_bytes*pos2], aux, h->_bytes);
}

Heap* criaHeap(size_t tam, size_t bytes, int (*compar)(void*a, void*b)){
    Heap* ptr;
    ptr = (Heap*)malloc(sizeof(Heap));
        if(ptr == NULL) return NULL;

    tam++;  //Por ser 1-indexado, a posição 0 não será usada.
    ptr->_p = malloc(tam*bytes);
        if(ptr->_p == NULL) return NULL;
    ptr->_bytes = bytes;
    ptr->_maxTam = tam;
    ptr->_fim = 0;
    ptr->_compar = compar;

    return ptr;
}
void pushH(Heap* h, void* x){
    if(h == NULL || x == NULL) return;

    if(!fullH(h)){
        h->_fim++;
        memcpy(&(h->_p[h->_bytes * h->_fim]), x, h->_bytes);
        siftUpH(h, h->_fim);
    }
}

void* topH(Heap* h, void* storage){
    if(emptyH(h)) return NULL;
    memcpy(storage, &h->_p[h->_bytes * 1], h->_bytes);
    return storage;
}

void popH(Heap* h){
    if(h != NULL && !emptyH(h)){
        if(h->_fim > 0){
            memcpy(&h->_p[h->_bytes * 1], &h->_p[h->_bytes * h->_fim], h->_bytes);
            h->_fim--;
            siftDownH(h, 1);
        }
    }

}
void* clearH(Heap* h){
    if(h != NULL){
        free(h->_p);
        free(h);
    }
    return NULL;
}

int fullH(Heap* h){
    return h->_fim == h->_maxTam-1;
}

int emptyH(Heap* h){
    return h->_fim == 0;
}

void siftUpH(Heap* h, size_t filho){
    size_t pai = filho/2;
    // Enquanto o filho tiver maior prioridade que seu pai, e o filho tiver pai...
    while(filho > 1 && h->_compar(&h->_p[h->_bytes*filho], &h->_p[h->_bytes*pai]) > 0){
        trocaH(h, filho, pai);

        filho = pai;
        pai = filho/2;
    }
}

void siftDownH(Heap* h, size_t pai){
    size_t filho = 2*pai;           // filho é o filho prioritário. Supomos inicialmente que o da esquerda o seja.

    while(filho <= h->_fim){         // Enquanto tiver ao menos o filho da esquerda...

        if(filho+1 <= h->_fim){     // Se tiver o filho da direita também...
            // Se o filho da direita tiver prioridade sobre o da esquerda, o filho maior será o da direita.
            if(h->_compar(&h->_p[h->_bytes * (filho+1)], &h->_p[h->_bytes * filho]) > 0)
                filho = filho+1;
        }

        // Se o filho de maior prioridade tiver mais prioridade que o pai...
        if(h->_compar(&h->_p[h->_bytes * filho], &h->_p[h->_bytes * pai]) > 0){
            trocaH(h, pai, filho);
            pai = filho;
            filho = 2*pai;
        }
        else break;

    }

}




