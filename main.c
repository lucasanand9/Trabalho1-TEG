//usar gcc main.c grafo.c -lm  para compilar
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

    float matrizEuclidiana[150][150];
    float matrizNormal[150][150];
    int matrizAdjacente[150][150];
    int grupoA[150];
    int grupoB[150];

int main(int argc, char *argv[]){
    int opcao;
    Flor *vet;
    printf("(0) Carregar a base de dados\n(1) Carregar a persistencia\nEscolha uma opcao:\n");
    scanf("%i", &opcao);
    switch(opcao){
        case 0:
            vet = lerCSV(argv[1]);
            distanciaEuc(vet, matrizEuclidiana);
            normalizaMatriz(matrizEuclidiana, matrizNormal);
            matrizAdj(matrizNormal, 0.2, matrizAdjacente);
            gravarCSV(matrizEuclidiana, matrizNormal, matrizAdjacente);
        break;
        case 1:
            lerPersistencia(matrizAdjacente, "grafo.csv");
        break;
    }
    
    DFS(matrizAdjacente, 0, grupoA);
    for (int i = 0; i < 150; i++){
        if (grupoA[i] == 0){
            DFS(matrizAdjacente, i, grupoB);
        }
        
    }
    printf("Acuracia: %lf\n", acuracia(grupoA, grupoB, vet));
    // printGrupos(grupoA);
    // printf("-------------------------------\n\n");
    // printGrupos(grupoB);
    // printGrafo(matrizAdjacente);
    
}