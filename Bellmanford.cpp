#include <iostream>
#include <limits.h>
#include <stdlib.h>
using namespace std;

#define max 100
#define infinity INT_MAX
#define nil -1

int n;                                                                     // Global variables 
int adj[max][max];                                              // Adjacency matrix to represent the graph 
int predecessor[max];
int pathlength[max];                                          // Array to store shortest path lengths
int ispresent_in_queue[max];
int front, rear;                                                    // Front and rear pointers for queue implementation 
int queue[max];

void initialize_queue();
void insert_queue(int u);
int delete_queue();
int isempty_queue();
void create_graph();
void findpath(int s, int v);
int bellmanford(int s);

int main() {
    int flag, s, v;                                                 // Variables for algorithm control and user input
    create_graph();
    cout << "Enter source vertex: ";
    cin >> s;
    flag = bellmanford(s);                                   // Call Bellman-Ford algorithm 
    if (flag == -1) {	                             // Check if negative cycle exists
        cout << "Error: Negative cycle in graph" << endl;
        exit(1);
    }
    while (1) {
        cout << "Enter destination vertex (-1 to quit): ";
        cin >> v;
        if (v == -1)
            break;
        if (v < 0 || v >= n)
            cout << "This vertex does not exist";
        else if (v == s)
            cout << "Source and destination vertices are same" << endl;
        else if (pathlength[v] == infinity)
            cout << "There is no path from source to destination vertex" << endl;
        else
            findpath(s, v);                                      // Call function to find shortest path and print it
    }
    return 0;
}

void findpath(int s, int v) {
    int i, u;                                                    // Variables for iteration and predecessor
    int path[max];
    int shortdist = 0;
    int count = 0;
                                                                     // Loop until source vertex is reached
    while (v != s) {
        count++;
        path[count] = v;
        u = predecessor[v];
        shortdist += adj[u][v];                             // Add edge weight to shortest distance
        v = u;
    }
    count++;
    path[count] = s;
    cout << "Shortest path is: ";                         // Loop to print shortest path
    for (i = count; i >= 1; i--)
        cout << path[i];
    cout<<endl;
    cout << "Shortest distance is: " << shortdist << endl;
}
			// Function to implement Bellman-Ford algorithm for single source shortest path
int bellmanford(int s) {
    int i, current;                                             // Variables for iteration and current vertex
    for (i = 0; i < n; i++) {
        predecessor[i] = nil;
        pathlength[i] = infinity;
        ispresent_in_queue[i] = false;
    }
    initialize_queue();				// Call function to initialize queue
    pathlength[s] = 0;
    insert_queue(s);
    ispresent_in_queue[s] = true;
    while (!isempty_queue()) {
        current = delete_queue();
        ispresent_in_queue[current] = false;

        for (i = 0; i < n; i++) {			// Loop until queue is empty
            if (adj[current][i] != 0 && pathlength[i] > pathlength[current] + adj[current][i]) {
                pathlength[i] = pathlength[current] + adj[current][i];
                predecessor[i] = current;
                if (!ispresent_in_queue[i]) {
                    insert_queue(i);
                    ispresent_in_queue[i] = true;
                }
            }
        }
    }
    							// Check for negative cycles
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != 0 && pathlength[j] > pathlength[i] + adj[i][j]) {
                return -1; // Negative cycle detected
            }
        }
    }
    return 1;						// Return success
}

void initialize_queue() {					// Function to initialize the queue
    for (int i = 0; i < max; i++)
        queue[i] = 0;
    rear = -1;
    front = -1;
}

int isempty_queue() {					// Function to check if the queue is empty
    if (front == -1 || front > rear)
        return 1;
    else
        return 0;
}

void insert_queue(int added_item) {			// Function to insert vertex into the queue
    if (rear == max - 1) {
        cout << "Queue is full" << endl;
        exit(1);
    } else {
        if (front == -1)
            front = 0;
        rear = rear + 1;
        queue[rear] = added_item;
    }
}

int delete_queue() {					// Function to delete vertex from the queue 
    int d;
    if (front == -1 || front > rear) {
        cout << "Queue is empty" << endl;
        exit(1);
    } else {
        d = queue[front];
        front = front + 1;
    }
    return d;
}

void create_graph() {					// Function to create the graph
    int m_e, origin, destin, wt;
    cout << "Enter the number of vertices: ";
    cin >> n;
    m_e = n * (n - 1);
    for (int i = 1; i <= m_e; i++) {
        cout << "Enter edges (-1 -1 to quit) " << i << ":";
        cin >> origin >> destin;
        if ((origin == -1) && (destin == -1))
            break;
        cout << "Enter weight for this edge: ";
        cin >> wt;
        if (origin >= n || destin >= n || origin < 0 || destin < 0) {
            cout << "Invalid edge!" << endl;
        } else
            adj[origin][destin] = wt; 				// Set edge weight in adjacency matrix
    }
}
/*Output:-
Enter the number of vertices: 3
Enter edges (-1 -1 to quit) 1:0  0
Enter weight for this edge: 6
Enter edges (-1 -1 to quit) 2:0  1
Enter weight for this edge: 7
Enter edges (-1 -1 to quit) 3:0  2
Enter weight for this edge: 10
Enter edges (-1 -1 to quit) 4:1  1
Enter weight for this edge: 1
Enter edges (-1 -1 to quit) 5:1  2
Enter weight for this edge: -11
Enter edges (-1 -1 to quit) 6:2  0
Enter weight for this edge: 5
Enter source vertex: 0
Enter destination vertex (-1 to quit): 2
Shortest path is: 012
Shortest distance is: -4
Enter destination vertex (-1 to quit): 1
Shortest path is: 01
Shortest distance is: 7
Enter destination vertex (-1 to quit): 0
Source and destination vertices are same
Enter destination vertex (-1 to quit):
*/
