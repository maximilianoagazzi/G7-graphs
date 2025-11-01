#ifndef HEADER_H
#define HEADER_H
#include"include/list.h"
#include "graph.h"

graph* europe_graph_create();
void print_graph(graph* g, void print_elemens(void* a));
void print_array(void* value);
int* vector_with_vertexs_degree(graph* g);
void print_DFS(graph* g, void print_elem(void* ));
void print_BFS(graph* g, void print_elem(void* ));

#endif