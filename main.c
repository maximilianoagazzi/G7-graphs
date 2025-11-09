#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    printf("\n\nEl grafo 2 esta representado por:\n\n");
    graph* g2 = graph_create2();
    print_graph(g2, print_array);
    int path_count = path_count_A_to_B_digraph(g2, 0, 1);
    printf("\nLa cantidad de caminos de A hacia B en el grafo 2 es: %d\n", path_count);
    //Ejercicio 5

    printf("\nLos caminos desde %s hacia %s son:\n", (char*)graph_vertex_get(g2, 0), (char*)graph_vertex_get(g2, 1));
    print_all_paths(g2, 0, 1);
    //Ejercicio 6

    int cyclic = is_cyclic_digraph(g2);
    if(cyclic == 1) {
        printf("\nEl grafo g2 contiene al menos un ciclo\n");
    } else {
        printf("\nEl grafo g2 no contiene ningun ciclo\n");
    }
    //Ejercicio 7a

    graph* g3 = graph_create3();
    int start = is_start(g3);
    if(start == 1) {
        printf("\nEl grafo g3 tiene forma de estrella\n");
    } else {
        printf("\nEl grafo g3 no tiene forma de estrella\n");
    }
    //Ejercicio 7b

    graph* g4 = graph_create4();
    int circular = is_circular(g4);
    if(circular == 1) {
        printf("\nEl grafo g4 puede ser representado por una lista circular\n");
    } else {
        printf("\nEl grafo g4 no puede ser representado por una lista circular\n");
    }
    //Ejercicio 7c

    graph* g5 = graph_create5();
    stack* s1 = stack_new();
    Dijkstra_path(g5, 0, 10, s1);
    printf("\nEl camino mas corto del vertice A hacia el vertice K en g5 es:\n");
    print_stack(s1, print_array);
    stack_free(&s1, 0);
    //Ejercicio 8

    table_elem* table = Dijkstra(g5, 0);
    printf("\n\nLos caminos hacia todos los vertices desde A en el grafo g5 son:\n");
    print_table_paths(g5, table, graph_vertex_count(g5), 0);
    //Ejercicio 9

    graph* g6 = transpose_digraph(g2, string_copy);
    printf("\nEl grafo transpuesto de g2 es:\n\n");
    print_graph(g6, print_array);
    //Ejercicio 10

    graph* g7 = graph_create7();
    printf("\nEl digrafo g7 impreso en orden topologico es:\n");
    topological_print(g7);
    printf("\n");
    //Ejercicio 11

    graph_destroy(&g1, 0);
    graph_destroy(&g2, 0);
    graph_destroy(&g3, 0);
    graph_destroy(&g4, 0);
    graph_destroy(&g5, 0);
    graph_destroy(&g6, 1);
    graph_destroy(&g7, 0);
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

int is_cyclic_digraph(graph* g)  //Ejercicio 7a
{
    if(g == NULL) return -1;

    int n = graph_vertex_count(g);
    int r = 0, i = 0;
    int* visited = (int* )calloc(n, sizeof(int));

    while(i<n && r != 1) {
        r = is_cyclic_aux(g, i, i, visited);
        i++;
    }
    free(visited);

    return r;
}

int is_cyclic_aux(graph* g, int start, int current, int* visited)  //Ejercicio 7a
{
    visited[current] = 1;
    int path = 0, j = 0;

    while(j<graph_vertex_count(g) && path != 1) {
        if(graph_edge_weight(g, current, j) > 0) {
            if(visited[j] == 0)
                path = is_cyclic_aux(g, start, j, visited);
            else if(j == start)
                path = 1;
        }
        j++;
    }
    visited[current] = 0;

    return path;
}

graph* graph_create3()  //Ejercicio 7b
{
    graph* g = graph_new();

    int a = graph_vertex_add(g, "a");
    int b = graph_vertex_add(g, "b");
    int c = graph_vertex_add(g, "c");
    int d = graph_vertex_add(g, "d");
    int e = graph_vertex_add(g, "e");

    graph_edge_add(g, a, b, 1);
    graph_edge_add(g, b, a, 1);
    graph_edge_add(g, a, c, 1);
    graph_edge_add(g, c, a, 1);
    graph_edge_add(g, a, d, 1);
    graph_edge_add(g, d, a, 1);
    graph_edge_add(g, a, e, 1);
    graph_edge_add(g, e, a, 1);

    return g;
}

int is_start(graph* g)  //Ejercicio 7b
{
    if(g == NULL) return -1;

    int r = 1;
    int center_p = is_start_aux(g);
    int n = graph_vertex_count(g), i = 0;

    if(center_p >= 0) {
        while(i<n && r == 1) {
            if(i != center_p && (graph_edge_weight(g, i, center_p) == 0 || graph_vertex_out_degree(g, i) > 1))
                r = 0;
            i++;
        }
    } else {
        r = 0;
    }

    return r;
}

int is_start_aux(graph* g)  //Ejercicio 7b
{
    if(g == NULL) return -2;

    int c = -1;
    int n = graph_vertex_count(g), i = 0;

    while(i<n && c == -1) {
        if(graph_vertex_out_degree(g, i) == n-1 && graph_edge_weight(g, i, i) == 0)
            c = i;
        i++;
    }

    return c;
}

graph* graph_create4()  //Ejercicio 7c
{
    graph* g = graph_new();

    int a = graph_vertex_add(g, "a");
    int b = graph_vertex_add(g, "b");
    int c = graph_vertex_add(g, "c");
    int d = graph_vertex_add(g, "d");
    int e = graph_vertex_add(g, "e");

    graph_edge_add(g, a, b, 1);
    graph_edge_add(g, b, a, 1);
    graph_edge_add(g, b, c, 1);
    graph_edge_add(g, c, b, 1);
    graph_edge_add(g, c, d, 1);
    graph_edge_add(g, d, c, 1);
    graph_edge_add(g, d, e, 1);
    graph_edge_add(g, e, d, 1);
    graph_edge_add(g, e, a, 1);
    graph_edge_add(g, a, e, 1);

    return g;
}

int is_circular(graph* g)  //Ejercicio 7c
{
    if(g == NULL) return -1;

    int r = -1;
    int n = graph_vertex_count(g);

    if(n == 1 && graph_edge_weight(g, 0, 0) == 1)
        r = 1;
    else if(n < 3)
        r = 0;

    if(n >= 3) {
        for(int i=0; i<n && r==-1; i++)
            if(graph_vertex_out_degree(g, i) != 2) r = 0;

        if(r == -1) {
            int* visited = (int* )calloc(n, sizeof(int));
            r = is_circular_aux(g, 0, 0, -1, visited);

            for(int i=0; i<n && r==1; i++)
                if(visited[i] == 0) r = 0;

            free(visited);
        }
    }

    return r;
}

int is_circular_aux(graph* g, int start, int current, int parent, int* visited)  //Ejercicio 7c
{
    visited[current] = 1;
    int n = graph_vertex_count(g);
    int circular = -1;

    for(int i=0; i<n && circular==-1; i++) {
        if(graph_edge_weight(g, current, i) == 1 && i != parent) {
            if(visited[i] == 1) {
                if(i != start) circular = 0;
                if(i == start) circular = 1;
            }  else {
                circular = is_circular_aux(g, start, i, current, visited);
            }
        }
    }

    return circular;
}

graph* graph_create5()  //Ejercicio 8
{
    graph* g = graph_new();

    int A = graph_vertex_add(g, "A");
    int B = graph_vertex_add(g, "B");
    int C = graph_vertex_add(g, "C");
    int D = graph_vertex_add(g, "D");
    int E = graph_vertex_add(g, "E");
    int F = graph_vertex_add(g, "F");
    int G = graph_vertex_add(g, "G");
    int H = graph_vertex_add(g, "H");
    int I = graph_vertex_add(g, "I");
    int J = graph_vertex_add(g, "J");
    int K = graph_vertex_add(g, "K");

    graph_edge_add(g, A, B, 3);
    graph_edge_add(g, A, E, 5);
    graph_edge_add(g, A, H, 4);
    graph_edge_add(g, B, C, 2);
    graph_edge_add(g, B, F, 7);
    graph_edge_add(g, C, D, 3);
    graph_edge_add(g, C, G, 6);
    graph_edge_add(g, C, F, 2);
    graph_edge_add(g, D, K, 7);
    graph_edge_add(g, E, B, 5);
    graph_edge_add(g, E, F, 4);
    graph_edge_add(g, E, H, 7);
    graph_edge_add(g, F, G, 4);
    graph_edge_add(g, F, J, 3);
    graph_edge_add(g, G, D, 2);
    graph_edge_add(g, G, K, 8);
    graph_edge_add(g, G, J, 4);
    graph_edge_add(g, H, F, 5);
    graph_edge_add(g, H, I, 2);
    graph_edge_add(g, I, F, 4);
    graph_edge_add(g, I, J, 6);
    graph_edge_add(g, J, K, 2);

    return g;
}

void print_stack(stack* s, void print(void* ))  //Ejercicio 8
{
    if(s == NULL) return;

    stack* aux = stack_new();
    while(!stack_is_empty(s)) {
        void* elem = pop(s);
        print(elem);
        if(stack_length(s) > 0) printf("--> ");
        push(aux, elem);
    }

    while(!stack_is_empty(aux))
        push(s, pop(aux));
}

void Dijkstra_path(graph* g, int from, int to, stack* s)  //Ejercicio 8
{
    if(g == NULL) return;

    int n = graph_vertex_count(g);
    table_elem* table = (table_elem* )calloc(n, sizeof(table_elem));
    int* visited = (int* )calloc(n, sizeof(int));
    Dijkstra_aux(g, from, table, visited);

    if (table[to].cost != GRAPH_INF) {
        push(s, graph_vertex_get(g, to));
        if(from != to) {
            int pred = table[to].pred;
            while(pred != from) {
                push(s, graph_vertex_get(g, pred));
                pred = table[pred].pred;
            }
            push(s, graph_vertex_get(g, from));
        }
    } else {
        printf("No existe camino desde %s hasta %s\n", graph_vertex_get(g, from), graph_vertex_get(g, to));
    }

    free(table);
    free(visited);
}

void Dijkstra_aux(graph* g, int from, table_elem* table, int* visited)  //Ejercicio 9
{
    visited[from] = 1;
    int n = graph_vertex_count(g);
    int min_cost_index = ini_table(g, from, table);
    int min_cost = GRAPH_INF;

    int current = min_cost_index;
    for(int i=1; i<n; i++) {
        if (min_cost_index == -1) break;
        visited[current] = 1;

        for(int j=0; j<n; j++) {
            int w = graph_edge_cost(g, current, j);
            if(visited[j] == 0) {
                if(w != GRAPH_INF && table[current].cost != GRAPH_INF && table[j].cost > w + table[current].cost) {
                    table[j].cost = w + table[current].cost;
                    table[j].pred = current;
                }
                if(table[j].cost < min_cost) {
                    min_cost = table[j].cost;
                    min_cost_index = j;
                }
            }
        }

        current = min_cost_index;
        min_cost = GRAPH_INF;
    }
}

int ini_table(graph* g, int from, table_elem* table)  //Ejercicio 9
{
    int min_cost = GRAPH_INF;
    int min_cost_index = -1;

    table[from].cost = 0;
    table[from].pred = from;
    for(int j=0; j<graph_vertex_count(g); j++) {
        if(j != from) {
            table[j].cost = graph_edge_cost(g, from, j);
            table[j].pred = from;
        }
        if(table[j].cost < min_cost) {
            min_cost = table[j].cost;
            min_cost_index = j;
        }
    }

    return min_cost_index;
}

table_elem* Dijkstra(graph* g, int from)  //Ejercicio 9
{
    if(g == NULL) return NULL;

    int n = graph_vertex_count(g);
    table_elem* table = (table_elem* )calloc(n, sizeof(table_elem));
    int* visited = (int* )calloc(n, sizeof(int));
    Dijkstra_aux(g, from, table, visited);
    free(visited);
    
    return table;
}

void print_table_paths(graph* g, table_elem* table, int n, int from)  //Ejercicio 9
{
    if(table == NULL) return;

    stack* s = stack_new();
    for(int i=0; i<n; i++) {
        if (table[i].cost != GRAPH_INF) {
            push(s, graph_vertex_get(g, i));
            if(from != i) {
                int pred = table[i].pred;
                while(pred != from) {
                    push(s, graph_vertex_get(g, pred));
                    pred = table[pred].pred;
                }
                push(s, graph_vertex_get(g, from));
            }
            print_stack(s, print_array);
            printf("\n");
        } else {
            printf("No existe camino desde %d hasta %s\n", from, i);
        }
        while(!stack_is_empty(s))
            pop(s);
    }
    stack_free(&s, 0);
}

void* string_copy(void* elem)  //Ejercicio 10
{
    if(elem == NULL) return NULL;

    char* copy = (char* )malloc(sizeof(char)*(strlen((char* )elem) + 1));
    if(copy != NULL) {
        strcpy(copy, (char* )elem);
    }

    return copy;
}

graph* transpose_digraph(graph* g, void* copy_vertex(void* ))  //Ejercicio 10
{
    if(g == NULL) return NULL;

    graph* n = graph_new();

    if(n != NULL) {
        for(int i=0; i<graph_vertex_count(g); i++) {
            void* copy = copy_vertex(graph_vertex_get(g, i));
            if(copy == NULL) return NULL;
            graph_vertex_add(n, copy);
        }

        for(int i=0; i<graph_vertex_count(g); i++) {
            for(int j=0; j<graph_vertex_count(g); j++) {
                if(graph_edge_exists(g, i, j) == 1) 
                    graph_edge_add(n, j, i, graph_edge_weight(g, i, j));
            }
        }
    }

    return n;
}

graph* graph_create7()  //Ejercicio 11
{
    graph* g = graph_new();

    int A = graph_vertex_add(g, "A");
    int B = graph_vertex_add(g, "B");
    int C = graph_vertex_add(g, "C");
    int D = graph_vertex_add(g, "D");
    int E = graph_vertex_add(g, "E");

    graph_edge_add(g, A, B, 1);
    graph_edge_add(g, A, C, 1);
    graph_edge_add(g, B, D, 1);
    graph_edge_add(g, C, B, 1);
    graph_edge_add(g, C, E, 1);
    graph_edge_add(g, E, D, 1);

    return g;
}

void topological_print(graph* g)  //Ejercicio 11
{
    if(g == NULL) return;

    int n = graph_vertex_count(g);
    int* visited = (int* )calloc(n, sizeof(int));
    stack* s = stack_new();

    for(int i=0; i<n; i++) {
        if(visited[i] == 0) topological_aux(g, i, visited, s);
    }

    print_stack(s, print_array);

    stack_free(&s, 0);
    free(visited);
}

void topological_aux(graph* g, int v, int* visited, stack* s)  //Ejercicio 11
{
    visited[v] = 1;

    for(int j=0; j<graph_vertex_count(g); j++) {
        if(graph_edge_exists(g, v, j) == 1 &&  visited[j] == 0)
            topological_aux(g, j, visited, s);
    }

    push(s, graph_vertex_get(g, v));
}

