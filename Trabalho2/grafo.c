/* Aluno: Pedro Augusto Beserra da Silva Matrícula: 2321374*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h> 
#include "grafo.h" 

#define INFINITO FLT_MAX

typedef struct _no_fila {
    int info;
    struct _no_fila *prox;
} NoFila;

typedef struct _fila {
    NoFila *ini;
    NoFila *fim;
} Fila;

static Fila* criar_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

static void enfileirar(Fila* f, int v) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    novo->info = v;
    novo->prox = NULL;
    if (f->fim != NULL) f->fim->prox = novo;
    else f->ini = novo;
    f->fim = novo;
}

static int desenfileirar(Fila* f) {
    if (f->ini == NULL) return -1;
    int v = f->ini->info;
    NoFila* t = f->ini;
    f->ini = f->ini->prox;
    if (f->ini == NULL) f->fim = NULL;
    free(t);
    return v;
}

static int fila_vazia(Fila* f) {
    return (f->ini == NULL);
}

static void imprimir_fila(Fila* f) {
    NoFila* p = f->ini;
    printf("    [Fila]: { ");
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("}\n");
}

Grafo* criar_grafo(int n) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    if (g == NULL) exit(1);
    g->nv = n;
    g->na = 0;
    g->viz = (Viz**) malloc(n * sizeof(Viz*));
    for (int i = 0; i < n; i++) g->viz[i] = NULL;
    return g;
}

void inserir_aresta(Grafo* g, int origem, int destino, float peso) {

    Viz* novo1 = (Viz*) malloc(sizeof(Viz));
    novo1->noj = destino;
    novo1->peso = peso;
    novo1->prox = g->viz[origem];
    g->viz[origem] = novo1;

    Viz* novo2 = (Viz*) malloc(sizeof(Viz));
    novo2->noj = origem;
    novo2->peso = peso;
    novo2->prox = g->viz[destino];
    g->viz[destino] = novo2;

    g->na++;
}

void liberar_grafo(Grafo* g) {
    for (int i = 0; i < g->nv; i++) {
        Viz* p = g->viz[i];
        while (p != NULL) {
            Viz* t = p;
            p = p->prox;
            free(t);
        }
    }
    free(g->viz);
    free(g);
}

/* --- Letra A --- */
void imprimir_lista_adjacencias(Grafo* g) {
    printf("--------------------------------------------------\n");
    for (int i = 1; i < g->nv; i++) {
        printf("  Vertice %2d -> ", i);
        Viz* p = g->viz[i];
        if (!p) printf("NULL");
        while (p != NULL) {
            printf("[Dest:%d | %.0f] -> ", p->noj, p->peso);
            p = p->prox;
        }
        printf("NULL\n");
    }
    printf("--------------------------------------------------\n");
}

/* --- Letra B --- */
void executar_bfs(Grafo* g, int inicio) {
    int* visitado = (int*) calloc(g->nv, sizeof(int));
    Fila* f = criar_fila();
    int passo = 1;

    printf("\nIniciando BFS a partir de %d:\n", inicio);
    
    visitado[inicio] = 1;
    enfileirar(f, inicio);
    printf("  Passo 0: Visita %d. ", inicio);
    imprimir_fila(f);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);
        printf("\n  Passo %d: Removeu %d. Explorando vizinhos:\n", passo++, u);
        
        Viz* p = g->viz[u];
        while (p != NULL) {
            int v = p->noj;
            if (!visitado[v]) {
                visitado[v] = 1;
                enfileirar(f, v);
                printf("    -> %d eh novo (Marca e Enfileira).", v);
            } else {
                printf("    -> %d ja visitado.", v);
            }
            p = p->prox;
        }
        printf("\n");
        imprimir_fila(f);
    }
    
    printf("\nFim da BFS.\n");
    free(visitado);
    free(f);
}

/* --- Letra C --- */
static void mostrar_vetor_dist(float* dist, int n) {
    printf("    [Distancias]: ");
    for(int i=1; i<n; i++) {
        if(dist[i] == INFINITO) printf("Infito ");
        else printf("%.0f   ", dist[i]);
    }
    printf("\n");
}

void executar_dijkstra(Grafo* g, int inicio) {
    float* dist = (float*) malloc(g->nv * sizeof(float));
    int* pai = (int*) malloc(g->nv * sizeof(int));
    int* aberto = (int*) malloc(g->nv * sizeof(int));

    for (int i = 0; i < g->nv; i++) {
        dist[i] = INFINITO;
        pai[i] = -1;
        aberto[i] = 1; 
    }
    dist[inicio] = 0;

    printf("\nEstado Inicial Dijkstra:\n");
    mostrar_vetor_dist(dist, g->nv);

    for (int i = 0; i < g->nv; i++) {
        float min = INFINITO;
        int u = -1;
        for (int v = 1; v < g->nv; v++) {
            if (aberto[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1) break;

        aberto[u] = 0;
        printf("\n  > Fechou o no %d (dist %.0f). Relaxando vizinhos...\n", u, dist[u]);

        Viz* p = g->viz[u];
        while (p != NULL) {
            int v = p->noj;
            float peso = p->peso;
            if (aberto[v]) {
                if (dist[u] + peso < dist[v]) {
                    printf("    * Relaxou (%d->%d). Nova dist: %.0f\n", u, v, dist[u]+peso);
                    dist[v] = dist[u] + peso;
                    pai[v] = u;
                }
            }
            p = p->prox;
        }
        mostrar_vetor_dist(dist, g->nv);
    }
    printf("\n--- Caminhos minimos a partir %d ---\n", inicio);
    for (int i = 1; i < g->nv; i++) {
        if (i == inicio) continue;
        printf("Destino %2d | Custo: %2.0f | Caminho: ", i, dist[i]);
        
        if (dist[i] == INFINITO) {
            printf("Sem caminho\n");
        } else {
            int caminho[MAX_NOS];
            int tam = 0;
            int atual = i;
            while (atual != -1) {
                caminho[tam++] = atual;
                atual = pai[atual];
            }
            for (int k = tam - 1; k >= 0; k--) {
                printf("%d%s", caminho[k], (k > 0) ? " -> " : "");
            }
            printf("\n");
        }
    }

    free(dist);
    free(pai);
    free(aberto);
}