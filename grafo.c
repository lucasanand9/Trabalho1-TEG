#include "grafo.h"

Flor * lerCSV(FILE *f, char *fileName){
    f = fopen(fileName, "r");
    if (!f){
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }
    
    Flor vet[150];
    float a,b,c,d;
    char p[50];
    int i = 0;
    while (fscanf(f, " %s%f%f%f%f", p,&a,&b,&c,&d) != NULL ){
        vet[i].sepalaAltura = a;
        vet[i].sepalaLargura = b;
        vet[i].petalaAltura = c;
        vet[i].petalaLargura = d;
        i++;
    }
    return vet;
}