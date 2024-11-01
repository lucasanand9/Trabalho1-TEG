//usar gcc main.c grafo.c -lm  para compilar
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

    float matrizEuclidiana[150][150];
    float matrizNormal[150][150];
    int matrizAdjacente[150][150];
    int grupoA[150];
    int grupoB[150];
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
    
    //achando todos os subgrafos
    for (int i = 0; i < 150; i++){
        int vdd = 1;
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

    int maiores[150];

    for (int i = 0; i < 150; i++){      
        maiores[i] = 0; 
        for (int j = 0; j < 150; j++){
            if (subGrupos[i][j] == 1){
                maiores[i]++;
            }
        }
    }

    //achando o indice dos dois maiores subgrafos
    int indice1, indice2;
    indice1 = indice2 = -1;
    int maior1, maior2;
    maior1 = maior2 = -2147483648;
    for (int i = 0; i < 150; i++){
        if (maiores[i] > maior1){
            maior2 = maior1;
            maior1 = maiores[i];
            indice2 = indice1;
            indice1 = i;
        }else if(maiores[i] > maior2 && maiores[i] != maior1){
            maior2 = maiores[i];
            indice2 = i;
        }
    }

    //indo para o calculo da media dos dois maiores subgrafos
    Flor a, b;
    a.petalaAltura = a.petalaLargura = a.sepalaAltura = a.sepalaLargura = 0;
    b.petalaAltura = b.petalaLargura = b.sepalaAltura = b.sepalaLargura = 0;

    //calculando a media do grupoA
    for (int i = 0; i < 150; i++){
        if (subGrupos[indice1][i] == 1){
            a.petalaAltura += vet[i].petalaAltura;
            a.petalaLargura += vet[i].petalaLargura;
            a.sepalaAltura += vet[i].sepalaAltura;
           a.sepalaLargura += vet[i].sepalaLargura;
        }
    }
    a.petalaAltura /= maiores[indice1];
    a.petalaLargura /= maiores[indice1];
    a.sepalaAltura /= maiores[indice1];
    a.sepalaLargura /= maiores[indice1];

    //calculando a media do grupoB
    for (int i = 0; i < 150; i++){
        if (subGrupos[indice2][i] == 1){
            b.petalaAltura += vet[i].petalaAltura;
            b.petalaLargura += vet[i].petalaLargura;
            b.sepalaAltura += vet[i].sepalaAltura;
           b.sepalaLargura += vet[i].sepalaLargura;
        }
    }
    b.petalaAltura /= maiores[indice2];
    b.petalaLargura /= maiores[indice2];
    b.sepalaAltura /= maiores[indice2];
    b.sepalaLargura /= maiores[indice2];

    //ir para o calculo da distancia euclidiana 
    float dist1, dist2;
    int indiceMaior1 = -1;
    int indiceMaior2 = -1;
    int indiceSub = -1;
    
    //achando o primeiro nodo do maior subgrafo
    for (int i = 0; i < 150; i++){
        if (subGrupos[indice1][i] == 1){
            indiceMaior1 = i;
            break;
        }        
    }
    //achando o primeiro nodo do segundo maior subgrafo
    for (int i = 0; i < 150; i++){
        if (subGrupos[indice2][i] == 1){
            indiceMaior2 = i;
            break;
        }        
    }
    
    //percorrendo a matriz de subgrafos para ir calculando a distancia em relacao aos dois maiores subgrafos
    for (int i = 0; i < 150; i++){

        if (i == indice1 || i == indice2){
            continue;
        }
        
        for (int j = 0; j < 150; j++){
            if (subGrupos[i][j] == 1){
               dist1 = distanciaEucInd(&a, &(vet[j])); //calculando a distancia do maior subgrafo
               dist2 = distanciaEucInd(&b, &(vet[j])); //calculando a distancia do segundo maior subgrafo
               indiceSub = j; //salvando o indice do primeiro elemento dos subgrafos menores
               break;
            }
        }

        //verificando em qual dos dois maiores subgrafos o menores vao se ligar
        if (dist1 <= dist2){
            matrizAdjacente[indiceMaior1][indiceSub] = 1;
            subGrupos[indice1][indiceSub] = 1;
        }else{
             matrizAdjacente[indiceMaior2][indiceSub] = 1;
             subGrupos[indice2][indiceSub] = 1;
        }
    }

    DFS(matrizAdjacente, 0, grupoA);
    for (int i = 0; i < 150; i++){
        if (grupoA[i] == 0){
            DFS(matrizAdjacente, i, grupoB);
            break;
        }
    }

    for (int i = 0; i < qtdSubGrpos; i++){
        printf("-------------------------\n\n");
        printf("Indice: %i\n", i);
        printGrupos(subGrupos[i]);
    }
    

    // printf("-------------------------------\n\n");
    // printf("Grupo A:\n");
    // printGrupos(grupoA);
    // printf("-------------------------------\n\n");
    // printf("Grupo B:\n");
    // printGrupos(grupoB);
    // printf("-------------------------------\n\n");

    printf("Quantidade de subGrafos: %i\n", qtdSubGrpos);
    printf("Acuracia: %lf\n", acuracia(subGrupos[indice1], subGrupos[indice2], maior1, maior2, vet));
    printf("-------------------------------\n\n");
    printf("Indice: %i\n", indice1);
    printf("Tamanho: %i\n", maior1);

    printGrupos(subGrupos[indice1]);
    printf("-------------------------------\n\n");
    printf("Indice: %i\n", indice2);
    printf("Tamanho: %i\n", maior2);
    printGrupos(subGrupos[indice2]);
    // printGrafo(matrizAdjacente);
    
}