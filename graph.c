#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void* copy_elem(void* elem);

typedef struct _graph {
    vector* vertex;  //Lista de vertices
    matrix* adjacency;  //Matriz dinamica de adyacencia
} graph;

graph* graph_new()  //Crea un nuevo grafo con una capacidad inicial de 10 vertices
{
    graph* g = (graph* )malloc(sizeof(graph));
    if(g == NULL) return NULL;

    g->vertex = vector_new_with(10);
    g->adjacency = matrix_new(10, 10);
    if(g->vertex == NULL || g->adjacency == NULL) {
        if(g->vertex == NULL && g->adjacency != NULL) matrix_free(g->adjacency);
        if(g->vertex != NULL && g->adjacency == NULL) vector_free(g->vertex);

        free(g);
        g = NULL;
    }

    return g;
}

void graph_destroy(graph** g, int dinamic)  //Destruye el grafo y los elementos de la lista de vertices si corresponde
{
    if(g == NULL || *g == NULL) return;

    int n = vector_size((*g)->vertex);
    if(dinamic == 1) {
        for(int i=0; i<n; i++) {
            void* v = vector_get((*g)->vertex, i);
            if(v != NULL) free(v);
        }
    }
    vector_free((*g)->vertex);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            void* m = matrix_get((*g)->adjacency, i, j);
            if(m != NULL) free(m);
        }
    }
    matrix_free((*g)->adjacency);

    free(*g);
    *g = NULL;
}

int graph_vertex_add(graph* g, void* elem)  //Añade un vertice, y si la matriz esta llena duplica su tamaño
{
    if(g == NULL) return -1;

    matrix* m = g->adjacency;
    if(vector_isfull(g->vertex) == 1) {
        if(matrix_resize(m, matrix_rows(m)*2, matrix_columns(m)*2) == 0) 
            return -1;
    }

    int ini = 0;
    void* set = &ini;
    
    int index = vector_size(g->vertex);  //Inicializa el nuevo vertice en 0
    vector_add(g->vertex, elem);
    for(int j=0; j<index; j++)
        matrix_set(m, index, j, copy_elem(set));
    for(int i=0; i<index; i++)
        matrix_set(m, i, index, copy_elem(set));
    matrix_set(m, index, index, copy_elem(set));

    return index;
}

void* graph_vertex_remove(graph* g, int index)  //Remueve un vertice 
{
    if(g == NULL || index >= vector_size(g->vertex) || index < 0) return NULL;

    matrix* m = g->adjacency;
    int size = vector_size(g->vertex);
    for(int j=0; j<size; j++)
        free(matrix_get(g->adjacency, index, j));
    for(int i=0; i<size; i++)
        if(i != index) free(matrix_get(g->adjacency, i, index));
    matrix_remove_row(m, index);
    matrix_remove_column(m, index);

    return vector_remove(g->vertex, index);
}

void* graph_vertex_get(graph* g, int index)  //devuelve un puntero al vertice buscado
{
    if(g == NULL || index < 0 || index >= vector_size(g->vertex)) return NULL;

    return vector_get(g->vertex, index);
}

int graph_vertex_index(graph* g, void* v)  //devuelve el indice del vertice buscado
{
    if(g == NULL || v == NULL) return -1;

    for(int i = 0; i < vector_size(g->vertex); i++) {
        if(vector_get(g->vertex, i) == v)
            return i;
    }

    return -1;
}

int graph_vertex_count(graph* g)  //devuelve la cantidad de vertices
{
    if(g == NULL) return -1;

    return vector_size(g->vertex);
}

int graph_vertex_out_degree(graph* g, int index)  //devuelve el grado de salida de un vertice
{
    if(g == NULL || index < 0 || index >= vector_size(g->vertex)) return -1;

    int degree = 0;
    for(int j=0; j<vector_size(g->vertex); j++) {
        int* val = (int* )matrix_get(g->adjacency, index, j);
        if(val != NULL && *val != 0)
            degree++;
    }

    return degree;
}

int graph_vertex_in_degree(graph* g, int index)  //devuelve el grado de entrada de un vertice
{
    if(g == NULL || index < 0 || index >= vector_size(g->vertex)) return -1;

    int degree = 0;
    for(int i=0; i<vector_size(g->vertex); i++) {
        int* val = (int* )matrix_get(g->adjacency, i, index);
        if(val != NULL && *val != 0)
            degree++;
    }

    return degree;
}

int graph_degree(graph* g)  //Devuelve el grado de un grafo
{
    if(g == NULL) return -1;

    int max_degree = 0;
    for(int i=0; i<vector_size(g->vertex); i++) {
        int v_degree = graph_vertex_out_degree(g, i);
        if(max_degree < v_degree)
            max_degree = v_degree;
    }

    return max_degree;
}

list* graph_vertex_adjacent_list(graph* g, int index)  //Devuelve una lista de adyacencia con punteros a los vertices
{
    if(g == NULL || index >= vector_size(g->vertex) || index < 0) return NULL;

    list* l = list_create();
    if(l != NULL) {
        int size = vector_size(g->vertex);
        for(int j=0; j<size; j++) {
            int* val = (int* )matrix_get(g->adjacency, index, j);
            if(val != NULL && *val != 0)
                list_append(l, vector_get(g->vertex, j));
        }
    }
    return l;
}

int graph_edge_weight(graph* g, int from, int to)  //devuelve el peso de la arista entre dos vertices
{
    if(g == NULL || from < 0 || to < 0 || from >= vector_size(g->vertex) || to >= vector_size(g->vertex)) return -1;

    int* val = (int*)matrix_get(g->adjacency, from, to);

    return (val != NULL) ? *val : -1;
}

int graph_edge_cost(graph* g, int from, int to)  //devuelve el costo de la arista entre dos vertices
{
    if(g == NULL || from < 0 || to < 0 || from >= vector_size(g->vertex) || to >= vector_size(g->vertex)) return GRAPH_INF;

    int weight = graph_edge_weight(g, from, to);

    return (weight != 0) ? weight : GRAPH_INF;
}

int graph_edge_exists(graph* g, int from, int to)  //devuelve 1 si existe arista, 0 si no, -1 si hay un error
{
    if(g == NULL || from < 0 || to < 0 || from >= vector_size(g->vertex) || to >= vector_size(g->vertex)) return -1;

    int* val = (int*)matrix_get(g->adjacency, from, to);
    if(val == NULL) return 0;

    return (*val != 0) ? 1 : 0;
}

int graph_edge_add(graph* g, int from, int to, int weight)  //agrega una arista con peso (minimo o no) al grafo
{
    if(g == NULL || from < 0 || to < 0 || from >= vector_size(g->vertex) || to >= vector_size(g->vertex)) return -1;

    int* val = (int*)matrix_get(g->adjacency, from, to);
    if(val == NULL) return 0;

    void* elem = &weight;
    int r = 0;
    if(*val == 0) {
        free(val);
        matrix_set(g->adjacency, from, to, copy_elem(elem));
        r = 1;
    }

    return r;
}

int graph_edge_remove(graph* g, int from, int to)  //remueve una arista del grafo
{
    if(g == NULL || from < 0 || to < 0 || from >= vector_size(g->vertex) || to >= vector_size(g->vertex)) return -1;

    int* val = (int*)matrix_get(g->adjacency, from, to);
    if(val == NULL) return 0;

    int ini = 0;
    void* elem = &ini;
    int r = 0;
    if(*val != 0) {
        free(val);
        matrix_set(g->adjacency, from, to, copy_elem(elem));
        r = 1;
    }

    return r;
}

void* copy_elem(void* elem)  //Auxiliar
{
    if(elem == NULL) return NULL;

    int* new_elem = (int* )malloc(sizeof(int));
    if(new_elem != NULL)
        *new_elem = *(int* )elem;

    return new_elem;
}