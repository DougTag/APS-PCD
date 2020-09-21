#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

typedef struct Nodo{
    char marca;
    unsigned int qtd;
    struct Nodo* esq;
    struct Nodo* dir;
}Nodo;

int compar(void* a, void* b){
    return (*(Nodo**)b)->qtd - (*(Nodo**)a)->qtd; // Se a for maior que b, então b tem prioridade.
}

Nodo* criaNodo(char marca, unsigned int qtd, Nodo* esq, Nodo* dir){
    Nodo* saida = (Nodo*)malloc(sizeof(Nodo));

    saida->marca = marca;
    saida->qtd = qtd;
    saida->esq = esq;
    saida->dir = dir;

    return saida;
}

void pegaRotulo(Nodo* raiz, char rotulo[][29], int bitmask, int nivel){
    if(raiz == NULL) return;

    if(raiz->marca != 0){
        for(int i = 0; i < nivel; i++){
            if(bitmask & (1<<i)) rotulo[(raiz->marca)-'a'][i] = '1';
            else rotulo[(raiz->marca)-'a'][i] = '0';
        }
        rotulo[(raiz->marca)-'a'][nivel] = '\0';

    }
    pegaRotulo(raiz->esq, rotulo, bitmask, nivel+1);
    pegaRotulo(raiz->dir, rotulo, bitmask|(1<<nivel), nivel+1);
}

int main(int argc, char *argv[]){
    unsigned int contagem[29] = {0};
    char rotulo[29][29];
    Heap *h;
    Nodo *aux, *tree;
    FILE* entrada, *saida;

    if(argc < 3){
        printf("Missing arguments.\n");
        exit(1);
    }

    entrada = fopen(argv[1], "rb");
    saida = fopen(argv[2], "wb");

    if(entrada == NULL){
        printf("The file does not exist, or there was an error opening the file.\n");
        exit(2);
    }
    if(saida == NULL){
        printf("An error has happened during the creation of the compressed archive. Please try again.\n");
        exit(3);
    }
    printf("%s %s\n", argv[1], argv[2]);

    while(!feof(entrada)){
        char auxc = (char)fgetc(entrada);
        if(auxc == ' ') contagem['z'+1-'a']++;
        else if(auxc == '\n') contagem['z'+2-'a']++;
        else contagem[auxc-'a']++;
    } contagem['z'+3-'a'] = 1;

    for(int i = 0; i<='z'-'a'; i++){
        printf("%c: %d\n", 'a'+i, contagem[i]);
    }
    printf(" : %d\n", contagem['z'-'a'+1]);
    printf("\\n: %d\n", contagem['z'-'a'+2]);
    printf("EOF: %d\n---\n", contagem['z'-'a'+3]);


    h = criaHeap(29, sizeof(Nodo*), compar);    // Uma heap mínima de ponteiros de Nodo.

    for(int i = 0; i<='z'-'a'+3; i++){
        aux = criaNodo('a'+i, contagem[i], NULL, NULL);
        pushH(h, &aux);
    }
    while(!emptyH(h)){
        Nodo *esq, *dir;
        topH(h, &esq);
        popH(h);
        if(emptyH(h)){
            tree = esq;
            break;
        }
        topH(h, &dir);
        popH(h);
        aux = criaNodo(0, esq->qtd+dir->qtd, esq, dir);
        pushH(h, &aux);
    }


    pegaRotulo(tree, rotulo, 0, 0);

    for(int i = 0; i<='z'-'a'; i++){
        printf("%c: %s\n", 'a'+i ,rotulo[i]);
    }
    printf(" : %s\n", rotulo['z'-'a'+1]);
    printf("\\n: %s\n", rotulo['z'-'a'+2]);
    printf("EOF: %s\n", rotulo['z'-'a'+3]);

    fseek(entrada, 0, SEEK_SET);

    char k = 0;
    unsigned int pos = 0;
    char caractere;
    fseek(saida, 0, SEEK_SET);
    caractere = fgetc(entrada);
    while(!feof(saida)){
        for(int i = 0; rotulo[caractere][i] != '\0'; i++, pos++){
            if(pos == 8) fwrite(&k, 1, 1, saida);
            if(rotulo[caractere][i] == '1') k = k|(1<<pos);
        }
        caractere = fgetc(entrada);
    }
    if(pos)
    //clearTree(tree);
    clearH(h);
    fclose(entrada);
    fclose(saida);
    exit(EXIT_SUCCESS);
    return 0;
}
