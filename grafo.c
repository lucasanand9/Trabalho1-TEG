#include "grafo.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

Flor * lerCSV( char *fileName){
    FILE *f = fopen(fileName, "r");
    if (!f){
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }
    
    Flor *vet = malloc(sizeof(Flor) * 150);
    float a,b,c,d;
    char p[50];
    int i = 0;
    char lixo[100];
    fscanf(f, "%[^\n]", lixo);
    while (fscanf(f, " %[^,],%f,%f,%f,%f", p,&a,&b,&c,&d) == 5){
        vet[i].sepalaAltura = a;
        vet[i].sepalaLargura = b;
        vet[i].petalaAltura = c;
        vet[i].petalaLargura = d;
        i++;
    }
    fclose(f);
    return vet;
}

void matrizAdj(float matrizEucNor[150][150], float distanciaMax, int matrizAdjc[150][150]){
    for(int i = 0; i < 150; i++){
        for(int j = 0; j < 150; j++){
            matrizAdjc[i][j] = 0;
        }
    }

    for(int i = 0; i < 150; i++){
        for(int j = 0; j < 150; j++){
            if(matrizEucNor[i][j] < distanciaMax && i != j){
                matrizAdjc[i][j] = 1;
            }
        }
    }
}

void normalizaMatriz(float matriz[150][150], float matrizNorm[150][150]) {
    float *maior, *menor;
    int i, j;

    menor = menorMatriz(matriz);
    maior = maiorMatriz(matriz);
 
    for(i=0; i < 150; i++) {
        for(j=0; j < 150; j++) {
            matrizNorm[i][j] = (matriz[i][j] - menor[0])/(maior[0]-menor[0]);
        }
    }
}

float * menorMatriz(float matriz[150][150]) {
    int i, j;
    int pi=1, pj=0;
    
    for(i=0; i < 150; i++) {
        for(j=0; j < 150; j++) {
            if(matriz[i][j] < matriz[pi][pj] && i != j) {
                pi = i;
                pj = j;
            }
        }
    }

    float *retorno = malloc(sizeof(float)*3);
    retorno[0] = matriz[pi][pj];
    retorno[1] = (float)pi;
    retorno[2] = (float)pj;
    return retorno;
}

float * maiorMatriz(float matriz[150][150]) {
    int i, j;
    int pi = 0, pj = 0;
    
    for(i=0; i < 150; i++) {
        for(j=0; j < 150; j++) {
            if(matriz[i][j] > matriz[pi][pj]) {
                pi = i;
                pj = j;
            }
        }
    }
    float *retorno = malloc(sizeof(float)*3);
    retorno[0] = matriz[pi][pj];
    retorno[1] = (float)pi;
    retorno[2] = (float)pj;
    return retorno;
}

void distanciaEuc(Flor *vet, float matriz[150][150]){
    int i, j;
    float distSA, distSL, distPA, distPL; //SA = Sepala Altura, PL = Petala Largura

    for(i = 0; i < 150; i++){
        for(j = 0; j < 150; j++){
            distSA = vet[i].sepalaAltura - vet[j].sepalaAltura;
            distSL = vet[i].sepalaLargura - vet[j].sepalaLargura;
            distPA = vet[i].petalaAltura - vet[j].petalaAltura;
            distPL = vet[i].petalaLargura - vet[j].petalaLargura;
            
            matriz[i][j] = (float)sqrt(pow(distSA,2) + pow(distSL,2) + pow(distPA,2) + pow(distPL,2));
        }
    }
}

void printGrafo(int matrizAdj[150][150]){
    for(int i = 0; i < 150; i++){
        for(int j = 0; j < 150; j++){
            printf("%i\t", matrizAdj[i][j]);
        }
        printf("\n");
    }
}

void gravarCSV(float matrizEuq[150][150], float matrizNor[150][150], int matrizAdj[150][150]){
    FILE *f = fopen("grafo.csv", "w");
    if(f == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    float *maiorEuclidiana = maiorMatriz(matrizEuq);
    float *menorEuclidiana = menorMatriz(matrizEuq);
    float *maiorNormalizada = maiorMatriz(matrizNor);
    float *menorNormalizada = menorMatriz(matrizNor);

    if(fprintf(f, "Quantidade de vértices lidos, %i\nMaior DE,%f,%i,%i\nMenor DE,%f,%i,%i\nMaior DEN,%f,%i,%i\nMenor DEN,%f,%i,%i\n", 150, maiorEuclidiana[0], (int)maiorEuclidiana[1], (int)maiorEuclidiana[2], menorEuclidiana[0], (int)menorEuclidiana[1], (int)menorEuclidiana[2], maiorNormalizada[0], (int)maiorNormalizada[1], (int)maiorNormalizada[2], menorNormalizada[0], (int)menorNormalizada[1], (int)menorNormalizada[2] ) == EOF){
        printf("Falha ao escrever no arquivo\n");
        return;
    }

    for(int i = 0; i < 150; i++){
        for(int j = 0; j<150; j++){
            if(matrizAdj[i][j] != 1){
                continue;
            }
            if(fprintf(f, "%i,%i\n", i, j) == EOF){
                printf("Falha ao escrever no arquivo\n");
                return;
            }
        }
    }

    fclose(f);
}

void printaMatriz(float matriz[150][150]){
    for(int i = 0; i < 150; i++){
        for(int j = 0; j < 150; j++){
            printf("%f\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void printFlor(Flor a){
    printf("%f %f %f %f\n", a.sepalaAltura, a.sepalaLargura, a.petalaAltura, a.petalaLargura);
}

void lerPersistencia(int matrizAdj[150][150], char *s){
    FILE *f = fopen(s, "r");
    if(!f){
        printf("Falha ao carregar o arquivo\n");
        return;
    }
    
    char lixo[50];
    int a,b;
    float c;
    fscanf(f, "%[^,],%i", lixo, &a);
    for(int i = 0; i < 5; i++){
        fscanf(f, "%[^,],%f,%i,%i", lixo, &c, &a, &b);
    }
    while(fscanf(f, "%i,%i", &a,&b) == 2 ){
        matrizAdj[a][b] = 1;
    }

}