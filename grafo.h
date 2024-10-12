typedef struct flor{
    float sepalaLargura;
    float sepalaAltura;
    float petalaLargura;
    float petalaAltura;
} Flor;

Flor * lerCSV(char * fileName);
void matrizAdj(float matrizEucNor[150][150], float distanciaMax, int matrizAdjc[150][150]);
void distanciaEuc(Flor *vet,float matriz[150][150]);
void normalizaMatriz(float matriz[150][150], float matrizNorm[150][150]);
float * menorMatriz(float matriz[150][150]);
float * maiorMatriz(float matriz[150][150]);
void printGrafo(int matrizAdj[150][150]);
void gravarCSV(float matrizEuq[150][150], float matrizNor[150][150], int matrizAdj[150][150]);
void printaMatriz(float matriz[150][150]);
void printFlor(Flor a);
void lerPersistencia(int matrizAdj[150][150], char *s);
