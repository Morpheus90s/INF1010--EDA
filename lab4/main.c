#include <stdio.h>
#include <stdlib.h>

#define MAX 4 
#define MIN 2 

struct no {
    int ndesc;              
    int chave[MAX];         
    struct no *ramo[MAX+1]; 
};
typedef struct no t_no;

void intervalo(t_no *arv, int lim_inf, int lim_sup);

t_no* cria_no_teste() {
    t_no* novo = (t_no*)malloc(sizeof(t_no));
    novo->ndesc = 0;
    for(int i = 0; i < MAX + 1; i++) novo->ramo[i] = NULL;
    return novo;
}


int main() {
    printf("Montando Arvore de Teste (Baseada na Q1)\n");

    t_no *raiz = cria_no_teste();
    raiz->ndesc = 1;
    raiz->chave[0] = 110;

    t_no *filhoEsq = cria_no_teste();
    filhoEsq->ndesc = 2;
    filhoEsq->chave[0] = 50;
    filhoEsq->chave[1] = 80;

    t_no *filhoDir = cria_no_teste();
    filhoDir->ndesc = 2;
    filhoDir->chave[0] = 140;
    filhoDir->chave[1] = 220;

    raiz->ramo[0] = filhoEsq; 
    raiz->ramo[1] = filhoDir; 

    printf("\nTeste 1: Intervalo entre 70 e 200 ( >70 e <200 )\n");
    printf("Esperado: 80, 110, 140\n");
    printf("Saida:\n");
    intervalo(raiz, 70, 200);

    printf("\nTeste 2: Intervalo amplo (0 a 300)\n");
    printf("Esperado: 50, 80, 110, 140, 220\n");
    printf("Saida:\n");
    intervalo(raiz, 0, 300);

    printf("\nTeste 3: Intervalo que nao pega ninguem (90 a 100)\n");
    printf("Esperado: (nenhuma saida)\n");
    printf("Saida:\n");
    intervalo(raiz, 90, 100);
    return 0;
}

void intervalo(t_no *arv, int lim_inf, int lim_sup) {
    if (arv == NULL) {
        return;
    }
    int i;

    for (i = 0; i < arv->ndesc; i++) {
        intervalo(arv->ramo[i], lim_inf, lim_sup);

        if (arv->chave[i] > lim_inf && arv->chave[i] < lim_sup) {
            printf("%d\n", arv->chave[i]);
        }
    }

    intervalo(arv->ramo[i], lim_inf, lim_sup);
}