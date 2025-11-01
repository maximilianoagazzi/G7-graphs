#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    graph* g1 = europe_graph_create();
    print_graph(g1, print_array);
    //Ejercicio de prueba

    int madrid_degree = graph_vertex_out_degree(g1, 0);
    printf("\nEl grado de %s es: %d\n", graph_vertex_get(g1, 0), madrid_degree);
    //Ejercicio 2

    int* v = vector_with_vertexs_degree(g1);
    printf("\nEl grado de cada vertice es: ");
    for(int i=0; i<graph_vertex_count(g1); i++) {
        printf("%d  ", v[i]);
    }
    printf("\n");
    //Ejercicio 3

    graph_destroy(&g1, 0);
    //Destruye los grafos
    return 0;
}

graph* europe_graph_create()  //Ejercicio de prueba
{
    graph* g = graph_new();

    int madrid = graph_vertex_add(g, "Madrid");
    int londres = graph_vertex_add(g, "Londres");
    int paris = graph_vertex_add(g, "Paris");
    int zurich = graph_vertex_add(g, "Zurich");
    int berlin = graph_vertex_add(g, "Berlin");
    int roma = graph_vertex_add(g, "Roma");

    graph_edge_add(g, madrid, londres, 28);
    graph_edge_add(g, londres, madrid, 28);
    graph_edge_add(g, madrid, paris, 14);
    graph_edge_add(g, paris, madrid, 14);
    graph_edge_add(g, madrid, roma, 65);
    graph_edge_add(g, roma, madrid, 65);
    graph_edge_add(g, londres, paris, 10);
    graph_edge_add(g, paris, londres, 10);
    graph_edge_add(g, londres, berlin, 14);
    graph_edge_add(g, berlin, londres, 14);
    graph_edge_add(g, paris, berlin, 36);
    graph_edge_add(g, berlin, paris, 36);
    graph_edge_add(g, paris, zurich, 12);
    graph_edge_add(g, zurich, paris, 12);
    graph_edge_add(g, berlin, roma, 24);
    graph_edge_add(g, roma, berlin, 24);

    return g;
}

void print_graph(graph* g, void print_elemens(void* a))  //Ejercicio de preuba
{
    if(g == NULL) return;

    for(int i=0; i<graph_vertex_count(g); i++) {
        for(int j=0; j<graph_vertex_count(g); j++) {
            printf("%4d", graph_edge_weight(g, i, j));
        }
        printf("\n");
    }

    printf("\n");
    for(int i=0; i<graph_vertex_count(g); i++) {
        print_elemens(graph_vertex_get(g, i));
        printf(" --> ");

        list* l = graph_vertex_adjacent_list(g, i);
        list_first(l);
        for(int j=0; j<list_length(l); j++) {
            print_elemens(list_get(l));
            if(j < list_length(l) - 1) printf(" -- ");
            list_next(l);
        }
        printf("\n");
        list_free(&l, 0);
    }
}

void print_array(void* elem)  //Ejercicio de prueba
{
    if(elem == NULL) return;

    printf("%s", (char*)elem);
}

int* vector_with_vertexs_degree(graph* g)  //Ejercicio 3
{
    if(g == NULL) return NULL;

    int cant_vertex = graph_vertex_count(g);
    int* v = (int* )malloc(sizeof(int)*cant_vertex);
    if(v != NULL) {
        for(int i=0; i<cant_vertex; i++) {
            v[i] = graph_vertex_out_degree(g, i);
        }
    }

    return v;
}

void print_DFS(graph* g, void print_elem(void* ))  //Ejercicio 4
{

}

void print_BFS(graph* g, void print_elem(void* ))  //Ejercicio 4
{

}