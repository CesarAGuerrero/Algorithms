/*
Prim's Minimum Spanning Tree (MST) algorithm. 
-Connects all nodes (vertices) in the least weighted path possible
*/ 

#include <stdio.h> //printf
#include <limits.h> //INT_MAX


#define V 5 //number of vertices used in example graph


int minKey(int key[], bool mstSet[]) //finds vertex with minimum key value //O(V)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}


void printMST(int parent[], int n, int graph[V][V]) //print //O(V)
{
	printf("Edge   Weight\n");
	for (int i = 1; i < V; i++)
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V]) //O(V) + O(V^2) + O(V) = O(V^2)
{
	int parent[V]; // Array to store constructed MST
	int key[V];   // Key values used to pick minimum weight edge in cut
	bool mstSet[V];  // To represent set of vertices not yet included in MST

					 // Initialize all keys as INFINITE
	for (int i = 0; i < V; i++)  //O (V)
		key[i] = INT_MAX, mstSet[i] = false;

	
	key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST 

	for (int count = 0; count < V - 1; count++)  //O(V * (V + V)) = O(V^2)
	{
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		int u = minKey(key, mstSet); //O(V)

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (int v = 0; v < V; v++) //O(V)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v]) //O(1)
				parent[v] = u, key[v] = graph[u][v];
	}

	// print the constructed MST
	printMST(parent, V, graph); //O(V)
}



int main()
{
	/*Example Graph
		   2    3
		(0)--(1)--(2)
		 |   / \   |
	    6| 8/   \5 |7
		 | /     \ |
		(3)-------(4)
		      9          */
	int graph[V][V] = { { 0, 2, 0, 6, 0 },
	{ 2, 0, 3, 8, 5 },
	{ 0, 3, 0, 0, 7 },
	{ 6, 8, 0, 0, 9 },
	{ 0, 5, 7, 9, 0 },
	};


	primMST(graph);

	return 0;
}

/*
Time Complexity
Worse: O(V * ( V + V )) = O(V^2)

Average: O(V * ( V + V )) = O (V^2)

In this example V is constant (V = 9) but the notation is for any number of V.

The complexity for both worse and average is the same because the algorithm is fully dependant on the value of V.
-We get O(V * (V + V)) from the for loops (and the for loop in minKey) in primMST()
-We get O(V) from minKey()
-Everything else is O(1) for if statements and variable updates
*/
