//usar gcc main.c grafo.c -lm  para compilar
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

    float matrizEuclidiana[150][150];
    float matrizNormal[150][150];
    int matrizAdjacente[150][150];

int main(int argc, char *argv[]){
    int opcao;
    printf("(0) Carregar a base de dados\n(1) Carregar a persistencia\nEscolha uma opcao:\n");
    scanf("%i", &opcao);
    switch(opcao){
        case 0:
            Flor *vet = lerCSV(argv[1]);
            distanciaEuc(vet, matrizEuclidiana);
            normalizaMatriz(matrizEuclidiana, matrizNormal);
            matrizAdj(matrizNormal, 0.3, matrizAdjacente);
            gravarCSV(matrizEuclidiana, matrizNormal, matrizAdjacente);
        break;
        case 1:
            lerPersistencia(matrizAdjacente, "grafo.csv");
        break;
    }

    printGrafo(matrizAdjacente);
    
}