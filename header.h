#ifndef HEADER_H
#define HEADER_H
#include"include/list.h"
#include "include/queue.h"
#include "include/stack.h"
#include "graph.h"

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

#endif