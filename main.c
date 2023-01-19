#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    char op = ' ';
    while(scanf("%c ", &op) != EOF){
        if(op == 'A'){
            build_graph();
        }
        else if(op == 'B'){
            int node = 0;
            scanf("%d", &node);
            insert_node(node);
        }
        else if(op == 'D'){
            int node = 0;
            scanf("%d", &node);
            delete_node(node);
        }
        else if(op == 'S'){
            int start = 0, end = 0;
            scanf("%d", &start);
            scanf("%d", &end);
            int d = shortestPath(start, end);
            if(d == INFINITY) d = -1;
            printf("Dijsktra shortest path: %d \n", d);
        }       
        else if(op == 'T'){
            int d = shortestPathTSP();
            if(d == INFINITY) d = -1;
            printf("TSP shortest path: %d \n", d);
        }

        #ifdef DEBUG_  
        printGraph();
        #endif   
    }
    
    deleteGraph();
    return 0;
}
