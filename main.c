//usar gcc main.c grafo.c -lm  para compilar
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

    float matrizEuclidiana[150][150];
    float matrizNormal[150][150];
    int matrizAdjacente[150][150];
    int subGrupos[150][150];

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
            matrizAdj(matrizNormal, 0.05, matrizAdjacente);
            gravarCSV(matrizEuclidiana, matrizNormal, matrizAdjacente);
        break;
        case 1:
            lerPersistencia(matrizAdjacente, "grafo.csv");
        break;
    }
    DFS(matrizAdjacente, 0, subGrupos[0]);
    int qtdSubGrpos = 1;
    int vdd = 1;
    for (int i = 0; i < 150; i++){
        if (subGrupos[qtdSubGrpos-1][i] == 0){
            for (int j = 0; j < 150; j++){
                if (subGrupos[j][i] != 0){
                    vdd = 0;
                    break;
                }
            } 
            if (vdd){
                qtdSubGrpos++;
                 DFS(matrizAdjacente, i, subGrupos[qtdSubGrpos-1]);
            }
        }
    }
    


    printf("Quantidade de subGrafos: %i\n", qtdSubGrpos);
    printf("Acuracia: %lf\n", acuracia(subGrupos[0], subGrupos[1], vet));
    // printGrupos(grupoA);
    // printf("-------------------------------\n\n");
    // printGrupos(grupoB);
    // printGrafo(matrizAdjacente);
    
}