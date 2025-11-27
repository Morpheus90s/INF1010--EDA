/* Aluno: Pedro Augusto Beserra da Silva Matrícula: 2321374*/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void carregar_grafo_do_trabalho(Grafo* g);

int main() {

    Grafo* g = criar_grafo(MAX_NOS);
    carregar_grafo_do_trabalho(g);

    printf("\nItem A: Representacao (Lista de Adjacencias)\n");
    imprimir_lista_adjacencias(g);

    printf("\nItem B: BFS a partir do no 3\n");
    executar_bfs(g, 3);

    printf("\nItem C: Dijkstra a partir do no 3\n");
    executar_dijkstra(g, 3);

    liberar_grafo(g);

    return 0;
}

void carregar_grafo_do_trabalho(Grafo* g) {
   
    inserir_aresta(g, 1, 9, 3);
    inserir_aresta(g, 1, 3, 3);
    inserir_aresta(g, 1, 10, 1);
    
    inserir_aresta(g, 2, 3, 4);
    inserir_aresta(g, 2, 10, 1);
    
    inserir_aresta(g, 3, 9, 4);
    inserir_aresta(g, 3, 4, 1);
    inserir_aresta(g, 3, 10, 2);
    
    inserir_aresta(g, 4, 7, 2);
    inserir_aresta(g, 4, 5, 2);
    
    inserir_aresta(g, 5, 7, 2);
    inserir_aresta(g, 5, 8, 4);
    
    inserir_aresta(g, 6, 7, 3);
    inserir_aresta(g, 6, 9, 1);
    
    inserir_aresta(g, 8, 9, 1);
    inserir_aresta(g, 8, 10, 2);
    
}