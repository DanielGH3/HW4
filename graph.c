#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "funcs.h"

int graph_size;
node* graph;

int index_from_num(int n){
    int index = -1;
    for(int i = 0; i < graph_size; i++) {
        if(graph[i].node_num == n || graph[i].node_num == -1){
            index = i;
            break;
        }
    }
    return index;
}

node* node_from_num(int n){
    int index = index_from_num(n);

    if(index == -1) return NULL;
    return &graph[index];
}

void create_new_node(int n){
    graph_size++;
    graph = realloc(graph, graph_size * sizeof(node));

    graph[graph_size - 1].node_num = n;
    graph[graph_size - 1].edges = malloc((graph_size - 1) * sizeof(edge));
}

void build_graph(){  
    deleteGraph();

    scanf("%d ", &graph_size);
    graph = malloc(graph_size * sizeof(node));
    for(int i = 0; i < graph_size; i++){
        graph[i].node_num = -1;
        graph[i].edges = malloc((graph_size - 1) * sizeof(edge));
        graph[i].num_of_edges = 0;
    }

    char c = ' ';
    while(scanf("%[n]", &c)){
        if(c != 'n') break;

        #ifdef DEBUG_
        printf("next \n");
        #endif
        
        int node = 0;
        scanf("%d", &node);
        insert_node(node);
        c = ' ';
    }
}

void insert_node(int n){
    int index = -1; //acutal index of node in array

    //Check if node exists
    index = index_from_num(n);

    //create new node if it doesnt exist
    if(index == -1){ 
        #ifdef DEBUG_   
        printf("create\n"); 
        #endif

        create_new_node(n);
        index = graph_size - 1;
    }else{
        graph[index].edges = realloc(graph[index].edges, graph_size * sizeof(edge)); 
    }
    
    graph[index].node_num = n;

    //read the connections + weights and assign them
    int count = 0;
    int connection = n;
    int weight = 0;

    while(scanf("%d", &connection) == 1){
        scanf("%d", &weight);
        graph[index].node_num = n;
        graph[index].edges[count].endpoint = connection;
        graph[index].edges[count].weight = weight;
        #ifdef DEBUG_   
        printf("recv : %d,%d\n", connection, weight);
        #endif
        count++;
    }

    graph[index].num_of_edges = count;
}

void delete_node(int n){
    #ifdef DEBUG_  
    printf("deleting : %d\n", n);
    #endif

    int del = index_from_num(n);//actual deleted node index
    if(del == -1) return;

    free(graph[del].edges);

    for(int i = del; i < graph_size - 1; i++){
        graph[i] = graph[i + 1];
    }

    graph_size--;
    graph = realloc(graph, graph_size * sizeof(node));

    for(int i = 0; i < graph_size; i++){
        for(int j = 0; j < graph[i].num_of_edges; j++){
            if(graph[i].edges[j].endpoint == n){
                while(j < graph[i].num_of_edges - 1){
                    graph[i].edges[i] = graph[i].edges[i + 1];
                    j++;
                }
                graph[i].num_of_edges--;
                graph[i].edges = realloc(graph[i].edges, graph[i].num_of_edges * sizeof(node));
                break;
            }
        }
    }
}

void printGraph(){
    printf("____________current graph____________\n");
    for(int i = 0; i < graph_size; i++){
        printf("node [%d] : \n", graph[i].node_num);
        printf("   |___edges : %d\n", graph[i].num_of_edges);
        printf("   |___edges : (end, weight)\n");

        for(int j = 0; j < graph[i].num_of_edges; j++){
            printf("         |___edge [%d] : (%d, %d)\n", j, graph[i].edges[j].endpoint, graph[i].edges[j].weight);
        }

        printf("\n");
    }
}

void deleteGraph(){
    for(int i = graph_size - 1; i >= 0; i--){
        delete_node(graph[i].node_num);
    }
    free(graph);
}

int nextPermutation(int *arr, int n) {
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i == -1) {
        reverse(arr, arr + n);
        return 0;
    }

    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    swap(arr + i, arr + j);
    reverse(arr + i + 1, arr + n);
    return 1;
}

int shortestPathTSP(){
    int num_nodes;
    scanf("%d ", &num_nodes);

    int * nodes = malloc((num_nodes) * sizeof(int));
    for(int i = 0; i < num_nodes; i++){
        scanf("%d", nodes + i);
    }

    int * indexes = malloc((num_nodes) * sizeof(int));
    for(int i = 0; i < num_nodes; i++){
        indexes[i] = i;
    }

    int shortest_path = INFINITY;
    do{ //Brute force O(n!)
        int temp_path = 0;
        for(int i = 0; i < num_nodes - 1; i++){
            int start = indexes[i];
            int end = indexes[i + 1];

            int p = shortestPath(nodes[start], nodes[end]);

            #ifdef DEBUG_
            printf("started %d -> %d, ended len = %d\n", start, end, p);
            #endif

            if(p >= 0 && p != INFINITY){
                temp_path += p;
            }else{
                temp_path = INFINITY;
                break;
            }
        }
        if(temp_path < shortest_path){
            shortest_path = temp_path;
        }
        #ifdef DEBUG_
        printf("TOTAL : %d\n", temp_path);
        #endif
    }while(nextPermutation(indexes, num_nodes));

    free(nodes);
    free(indexes);

    return shortest_path;
}

int shortestPath(int start, int end){
    if(index_from_num(end) == -1) return -1;
    if(index_from_num(start) == -1) return -1;
    if(start == end) return -1;

    int* dist = malloc(graph_size * sizeof(int));
    int* visited = malloc(graph_size * sizeof(int));

    int i, j, min_index, min;

    for (i = 0; i < graph_size; i++) {
        dist[i] = INFINITY; 
        visited[i] = 0;
    }

    dist[index_from_num(start)] = 0; 
    
    for (i = 0; i < graph_size - 1; i++) {
        min = INFINITY;

        for (j = 0; j < graph_size; j++) {
            if (!visited[j] && dist[j] <= min) {
                min = dist[j];
                min_index = j;
            }
        }

        visited[min_index] = 1;
        for (j = 0; j < graph[min_index].num_of_edges; j++) {

            int end = graph[min_index].edges[j].endpoint;
            end = index_from_num(end); //convert to index

            int weight = graph[min_index].edges[j].weight;

            if (!visited[end] && dist[min_index] != INFINITY && dist[min_index] + weight < dist[end]) {
                dist[end] = dist[min_index] + weight;
            }
        }
    }

    #ifdef DEBUG_       
    for (i = 0; i < graph_size; i++) {
        if (i != start) {
            printf("Shortest distance from node %d to %d is %d\n", start, graph[i].node_num, dist[i]);
        }
    }
    #endif 

    int distance =  dist[index_from_num(end)];

    free(dist);
    free(visited);

    return distance;
}
