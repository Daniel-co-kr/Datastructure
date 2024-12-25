#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100000
#define MAX_EDGES 500000

typedef struct _Edge {
	int u, v;
	int weight;
} Edge;

int N, M; // N: # of vertices, M: # of edges
Edge Edges[MAX_EDGES];
void sortEdges();

// Disjoint-Set Structure
typedef struct _DisjointSetNode {
	int parent;
	int size;
} DisjointSetNode;

DisjointSetNode DSNodes[MAX_VERTICES];
int findRoot(int u);
bool mergeSets(int u, int v);


int partition(Edge arr[], int low, int high) {
    int pivot = arr[high].weight;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].weight <= pivot) {
            i++;
            Edge temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Edge temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

//quickSort(Edges, 0, M-1); 
void quickSort(Edge arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high); 
    }
}    


int main() {
	int i, minCost = 0;
	scanf("%d%d", &N, &M);
	for (i = 0; i < M; i ++)
		scanf("%d%d%d", &Edges[i].u, &Edges[i].v, &Edges[i].weight);

	sortEdges(); // Sort edges in the increasing order of edge weights

	for (i = 0; i < N; i ++) { // Initialize DSNodes
		DSNodes[i].parent = i;
		DSNodes[i].size = 1;
	}
	for (i = 0; i < M; i ++) {
		if (mergeSets(Edges[i].u, Edges[i].v)) // If the nodes are not connected yet,
			minCost += Edges[i].weight;		// then add the edge into the minimum spanning tree
	}
	printf("%d\n", minCost);
	return 0;
}


void sortEdges() {
    quickSort(Edges, 0, M-1);
}

int findRoot(int u) {
	if (DSNodes[u].parent == u) return u;
	DSNodes[u].parent = findRoot(DSNodes[u].parent);
	return DSNodes[u].parent;
}

bool mergeSets(int u, int v) {
	u = findRoot(u);
	v = findRoot(v);
	if (u == v) return false;
	if (DSNodes[u].size > DSNodes[v].size) {
		DSNodes[u].size += DSNodes[v].size;
		DSNodes[v].parent = u;
	}
	else {
		DSNodes[v].size += DSNodes[u].size;
		DSNodes[u].parent = v;
	}
	return true;
}