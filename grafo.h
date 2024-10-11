#include <stdlib.h>
#include <stdio.h>

typedef struct flor{
    float sepalaLargura;
    float sepalaAltura;
    float petalaLargura;
    float petalaAltura;
} Flor;

Flor * lerCSV(FILE *f, char * fileName);
