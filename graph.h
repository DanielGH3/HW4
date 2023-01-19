#include <limits.h>

#ifndef GRAPH_
#define GRAPH_

//#define DEBUG_

#define INFINITY INT_MAX

typedef struct GRAPH_NODE_ node;

typedef struct edge_ {
    int weight;
    int endpoint;
} edge;


struct GRAPH_NODE_ {
    int node_num;
    int num_of_edges;
    edge* edges;
};

void build_graph();
void insert_node(int node);
void delete_node(int node);
void printGraph(); //for self debug
void deleteGraph();
int shortestPathTSP();
int shortestPath(int start, int end);
void TSP(edge head);
#endif
