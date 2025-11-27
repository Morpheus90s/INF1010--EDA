/* Aluno: Pedro Augusto Beserra da Silva Matrícula: 2321374*/

#ifndef GRAFO_H
#define GRAFO_H

#define MAX_NOS 11 

typedef struct _viz Viz;

struct _viz {
    int noj;        
    float peso;     
    Viz* prox;      
};

typedef struct _grafo Grafo;

struct _grafo {
    int nv;        
    int na;        
    Viz** viz;   
};

Grafo* criar_grafo(int n);

void liberar_grafo(Grafo* g);

void inserir_aresta(Grafo* g, int origem, int destino, float peso);

/* Letra A*/
void imprimir_lista_adjacencias(Grafo* g);

/* Letra B*/
void executar_bfs(Grafo* g, int inicio);

/* Letra C*/
void executar_dijkstra(Grafo* g, int inicio);

#endif