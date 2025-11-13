#ifndef HEADER_H
#define HEADER_H
#include"include/list.h"
#include "include/queue.h"
#include "include/stack.h"
#include "graph.h"

typedef struct {
    int cost;
    int pred;
} table_elem;

typedef struct _arc {
    int origin;
    int destiny;
    int cost;
    struct _arc* next;
} arc;

graph* europe_graph_create();
void print_graph(graph* g, void print_elemens(void* a));
void print_array(void* value);
int* vector_with_vertexs_degree(graph* g);
void DFS_visit(graph* g, int index, int* visited, void (*fnc)(void* ));
void DFS(graph* g, void (*fnc)(void* ));
void BFS_visit(graph* g, int start, int* visited, void (*fnc)(void*));
void BFS(graph* g, void (*fnc)(void* ));
graph* graph_create2();
int path_count_A_to_B_digraph(graph* g, int from, int to);
int count_paths_simple(graph* g, int from, int to, int* visited);
void print_path(graph* g, int* path, int path_len);
void print_all_paths(graph* g, int from, int to);
void print_all_paths_aux(graph* g, int from, int to, int* visited, int* path, int path_len);
int is_cyclic_digraph(graph* g);
int is_cyclic_aux(graph* g, int start, int neighbor, int* visited);
graph* graph_create3();
int is_start(graph* g);
int is_start_aux(graph* g);
graph* graph_create4();
int is_circular(graph* g);
int is_circular_aux(graph* g, int past, int current, int parent, int* visited);
graph* graph_create5();
void print_stack(stack* s, void print(void* ));
void Dijkstra_path(graph* g, int from, int to, stack* s);
table_elem* Dijkstra(graph* g, int from);
void Dijkstra_aux(graph* g, int from, table_elem* table, int* visited);
int ini_table(graph* g, int from, table_elem* table);
void print_table_paths(graph* g, table_elem* table, int n, int from);
void* string_copy(void* elem);
graph* transpose_digraph(graph* g, void* copy_vertex(void* ));
graph* graph_create7();
void topological_print(graph* g);
void topological_aux(graph* g, int v, int* visited, stack* s);
graph* graph_create8();
graph* coverage_tree_BFS(graph* g, int start);
graph* coverage_tree_BFS_aux(graph* g, int start, int* visited);
graph* graph_vertex_clone(graph* g);
graph* coverage_tree_DFS(graph* g, int start);
void coverage_tree_DFS_aux(graph* g, graph* a, int start, int* visited);
graph* graph_create9();
void* copy_int(void* elem);
void DFS_13_aux(graph* g, int index, int* visited);
list* get_mother_vertexs(graph* g);
void print_list_array(list* l);
arc* arc_new(int origin, int destiny, int cost);
void list_arc_insert_sort(arc** l, int origin, int destiny, int cost);
arc* arc_graph_create(graph* g);
graph* kruskal(graph* g);
void kruskal_aux(graph* k, arc* arcs, int* tree);

#endif