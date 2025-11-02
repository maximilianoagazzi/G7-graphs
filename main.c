#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    graph* g1 = europe_graph_create();
    printf("El grafo de Europa esta representado por:\n\n");
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
    free(v);
    printf("\n");
    //Ejercicio 3

    printf("\nEl grafo recorrido por profundidad es: ");
    DFS(g1, print_array);
    printf("\nEl grafo recorrido por amplitud es: ");
    BFS(g1, print_array);
    //Ejercicio 4

    printf("\n\nEl grafo 2 esta representado por:\n");
    graph* g2 = graph_create2();
    print_graph(g2, print_array);
    int path_count = path_count_A_to_B_digraph(g2, 0, 1);
    printf("\nLa cantidad de caminos de A hacia B en el grafo 2 es: %d\n", path_count);
    //Ejercicio 5

    printf("\nLos caminos desde %s hacia %s son:\n", (char*)graph_vertex_get(g2, 0), (char*)graph_vertex_get(g2, 1));
    print_all_paths(g2, 0, 1);

    graph_destroy(&g1, 0);
    graph_destroy(&g2, 0);
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
        printf("--> ");

        list* l = graph_vertex_adjacent_list(g, i);
        list_first(l);
        for(int j=0; j<list_length(l); j++) {
            print_elemens(list_get(l));
            if(j < list_length(l) - 1) printf("-- ");
            list_next(l);
        }
        printf("\n");
        list_free(&l, 0);
    }
}

void print_array(void* elem)  //Ejercicio de prueba
{
    if(elem == NULL) return;

    printf("%s ", (char*)elem);
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

void DFS_visit(graph* g, int index, int* visited, void (*fnc)(void* ))  //Ejercicio 4
{
    if(g == NULL || visited[index] != 0) return;

    visited[index] = 1;
    fnc(graph_vertex_get(g, index));

    for(int j=0; j<graph_vertex_count(g); j++) {
        if(graph_edge_weight(g, index, j) > 0 &&  visited[j] == 0)
            DFS_visit(g, j, visited, fnc);
    }
}

void DFS(graph* g, void (*fnc)(void* ))  //Ejercicio 4
{
    if(g == NULL) return;

    int* visited = (int* )calloc(graph_vertex_count(g), sizeof(int));
    for(int i=0; i<graph_vertex_count(g); i++) {
        if(visited[i] == 0) DFS_visit(g, i, visited, fnc);
    }

    free(visited);
}

void BFS_visit(graph* g, int start, int* visited, void (*fnc)(void*))  //Ejercicio 4
{
    if(g == NULL) return;

    queue* q = queue_new();
    int* first = (int* )malloc(sizeof(int));
    *first = start;
    enqueue(q, first);

    while(!queue_is_empty(q)) {
        int* idx_ptr = (int* )dequeue(q);
        int idx = *idx_ptr;
        free(idx_ptr);

        if(visited[idx] != 0) continue;

        visited[idx] = 1;
        fnc(graph_vertex_get(g, idx));

        for (int j=0; j<graph_vertex_count(g); j++) {
            if (graph_edge_weight(g, idx, j) > 0 && visited[j] == 0) {
                int* next = (int* )malloc(sizeof(int));
                *next = j;
                enqueue(q, next);
            }
        }
    }
    queue_free(&q, 1);
}

void BFS(graph* g, void (*fnc)(void*))  //Ejercicio 4
{
    if (g == NULL) return;

    int* visited = (int* )calloc(graph_vertex_count(g), sizeof(int));
    for (int i = 0; i < graph_vertex_count(g); i++) {
        if (!visited[i]) BFS_visit(g, i, visited, fnc);
    }

    free(visited);
}

graph* graph_create2()  //Ejercicio 5
{
    graph* g = graph_new();

    int a = graph_vertex_add(g, "a");
    int b = graph_vertex_add(g, "b");
    int c = graph_vertex_add(g, "c");
    int d = graph_vertex_add(g, "d");
    int e = graph_vertex_add(g, "e");
    int f = graph_vertex_add(g, "f");

    graph_edge_add(g, a, b, 1);
    graph_edge_add(g, a, c, 1);
    graph_edge_add(g, c, e, 1);
    graph_edge_add(g, d, a, 1);
    graph_edge_add(g, d, f, 1);
    graph_edge_add(g, e, a, 1);
    graph_edge_add(g, e, f, 1);
    graph_edge_add(g, f, b, 1);

    return g;
}

int path_count_A_to_B_digraph(graph* g, int from, int to)  //Ejercicio 5
{
    if(g == NULL || from < 0 || to < 0 || from >= graph_vertex_count(g) || to >= graph_vertex_count(g)) return -1;

    int* visited = (int* )calloc(graph_vertex_count(g), sizeof(int));
    int result = count_paths_simple(g, from, to, visited);
    free(visited);

    return result;
}

int count_paths_simple(graph* g, int from, int to, int* visited)  //Ejercicio 5
{
    if(from == to) return 1;

    visited[from] = 1;
    int path_count = 0;

    for(int i=0; i<graph_vertex_count(g); i++) {
        if(graph_edge_weight(g, from, i) > 0 && !visited[i]) {
            path_count += count_paths_simple(g, i, to, visited);
        }
    }
    visited[from] = 0;

    return path_count;
}

void print_path(graph* g, int* path, int path_len)  //Ejercicio 6
{
    for(int i=0; i<path_len; i++) {
        printf("%s", (char*)graph_vertex_get(g, path[i]));
        if(i < path_len - 1) printf(" -> ");
    }
    printf("\n");
}

void print_all_paths(graph* g, int from, int to)  //Ejercicio 6
{
    if (g == NULL || from < 0 || to < 0 || from >= graph_vertex_count(g) || to >= graph_vertex_count(g)) {
        printf("Error: parámetros inválidos\n");
        return;
    }

    int* visited = (int* )calloc(graph_vertex_count(g), sizeof(int));
    int* path = (int* )malloc(graph_vertex_count(g)*sizeof(int));

    print_all_paths_aux(g, from, to, visited, path, 0);

    free(visited);
    free(path);
}

void print_all_paths_aux(graph* g, int from, int to, int* visited, int* path, int path_len)  //Ejercicio 6
{
    visited[from] = 1;
    path[path_len] = from;
    path_len++;

    if(from == to) {
        print_path(g, path, path_len);
    } else {
        for(int i=0; i<graph_vertex_count(g); i++) {
            if(graph_edge_weight(g, from, i) > 0 && visited[i] == 0)
                print_all_paths_aux(g, i, to, visited, path, path_len);
        }
    }

    visited[from] = 0;
}

