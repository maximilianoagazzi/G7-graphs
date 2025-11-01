#ifndef GRAPH_H
#define GRAPH_H
#define GRAPH_INF 99999
#include "include/vector.h"
#include "include/matrix.h"
#include "include/list.h"

//Peso infinito = 0, peso minimo o existencia de camino = 1, peso ponderado >= 1

typedef struct _graph graph;

graph* graph_new(); //Crea un nuevo grafo con una capacidad inicial de 10 vertices
void graph_destroy(graph** g, int dinamic); //Destruye el grafo y los elementos de la lista de vertices si corresponde
int graph_vertex_add(graph* g, void* elem); //Añade un vertice, y si la matriz esta llena duplica su tamaño
void* graph_vertex_remove(graph* g, int index); //Remueve un vertice 
void* graph_vertex_get(graph* g, int index); //devuelve un puntero al vertice buscado
int graph_vertex_index(graph* g, void* v); //devuelve el indice del vertice buscado
int graph_vertex_count(graph* g); //devuelve la cantidad de vertices
int graph_vertex_out_degree(graph* g, int index); //devuelve el grado de salida de un vertice
int graph_vertex_in_degree(graph* g, int index); //devuelve el grado de entrada de un vertice
int graph_degree(graph* g); //Devuelve el grado de un grafo
list* graph_vertex_adjacent_list(graph* g, int index); //Devuelve una lista de adyacencia con punteros a los vertices
int graph_edge_weight(graph* g, int from, int to); //devuelve el peso de la arista entre dos vertices
int graph_edge_cost(graph* g, int from, int to); //devuelve el costo de la arista entre dos vertices
int graph_edge_exists(graph* g, int from, int to); //devuelve 1 si existe arista, 0 si no, -1 si hay un error
int graph_edge_add(graph* g, int from, int to, int weight); //agrega una arista con peso (minimo o no) al grafo
int graph_edge_remove(graph* g, int from, int to); //remueve una arista del grafo

#endif