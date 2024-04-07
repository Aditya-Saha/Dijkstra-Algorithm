#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6 // Number of vertices in the graph

int *status;
int *parent;
int *cost;

void dijkstra(int graph[V][V], int n, int vs, int vd, int *c);
void displayArray(int arr[], int size);

int main() {
    int c; // cost to travel to destination
    int vs; // source vertex
    int vd; // destination vertex

    // Allocate memory for global arrays
    status = (int *)calloc(V, sizeof(int));
    parent = (int *)calloc(V, sizeof(int));
    cost = (int *)calloc(V, sizeof(int));

    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {-1, 5, -1, 3, -1, -1},
        {5, -1, 1, 6, -1, -1},
        {-1, 1, -1, -1, 5, -1},
        {3, 6, -1, -1, 2, 4},
        {-1, -1, 5, 2, -1, 3},
        {-1, -1, -1, 4, 3, -1}
    };


    vs = 1;
    vd = 5; // Index corrected to 5 for the last vertex

    // Call Dijkstra's algorithm
    dijkstra(graph, V, vs, vd, &c);

    // Display the arrays
    printf("Status array is: ");
    displayArray(status, V);
    printf("Parent array is: ");
    displayArray(parent, V);
    printf("Cost array is: ");
    displayArray(cost, V);

    // Free allocated memory
    free(status);
    free(parent);
    free(cost);

    return 0;
}

void dijkstra(int graph[V][V], int n, int vs, int vd, int *c) {
    int lpv; // last permanent vertex
    int oc;  // old cost
    int nc;  // new cost
    int minCost;
    int i;

    // Initialize status, parent, and cost arrays
    for (int i = 0; i < n; i++) {
        status[i] = 0;
        parent[i] = vs;
        cost[i] = graph[vs][i];
    }
    status[vs] = 1;
    lpv = vs;

    while (status[vd] == 0) {
        i = 0;
        while (i < n) {
            if (status[i] == 0) {
                oc = cost[i];
                nc = cost[lpv] + graph[lpv][i];
                if ((nc < oc || oc < 0) && graph[lpv][i] > 0 && cost[lpv] > 0) {
                    cost[i] = nc;
                    parent[i] = lpv;
                }
            }
            i ++;
        }
        minCost = INT_MAX;
        i = 0;
        while (i < n) {
            if (status[i] == 0  && cost[i] > 0 && cost[i] < minCost) {
                minCost = cost[i];
                lpv = i;
            }
            i ++;
        }
        status[lpv] = 1;
    }
    *c = cost[vd];
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
