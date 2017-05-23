/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include<vector>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    //Create a vector to store the edges
    vector<Edge> edges;
    //Create arrays for distance, path and done
    int *dist  = new int [size + 1];
    int *path  = new int [size + 1];
    bool *done  = new bool[size + 1];

    int totalWeight = 0;
    //Initialize the arrays
    for(int v = 1; v<= size; v++)
    {
        dist[v] = INFINITY;
        path[v] = 0;
        done[v] = false;
    }
    //Choose starting vertex
    int v = 1;
    dist[v] = 0; //start can be any vertex
    done[v] = true;


    while (true)
    {
        //Point to the next value in the list
        Node *p = array[v].getFirst();
        //Loop through the list
        while(p)
        {
            int u = p->vertex;
            //Change initialized value
            //Only change value if it has not been visited and if there is a cheaper path
            if ( done[u]==false && dist[u] > p->weight )
            {
                dist[u] = p->weight;
                path[u] = v;
            }
            //Point to the next value in the list
            p = array[v].getNext();
        }
        //Point to the next value in the list
        v = find_smallest_undone_distance_vertex(dist, done);
        //If no vertex was found they have all been visited, break the loop
        if (v == 0) break; //exit the loop
        done[v] = true;

        // Push every edge into a vector
        edges.push_back(Edge(v, path[v], dist[v]));

    }

    // Print all edges
    for(int i = 0; i < edges.size(); i++)
    {
        display(edges[i].tail, edges[i].head, edges[i].weight);
        //Increment total weight
        totalWeight += edges[i].weight;
    }

    std::cout << "\nTotal weight = " << totalWeight << std::endl;
    //Deallocate memory
    delete[] done;
    delete[] path;
    delete[] dist;

}
int Graph::find_smallest_undone_distance_vertex(int dist[], bool done[]) const
{
    //Set v to a large value to start comparing
    int v = INFINITY+1;
    int vertex = 0;

    //Loop through the graph
    for (int i = 1; i <=size; i++)
    {
        //If vertex is not visited
        if (done[i]== false )
        {
            //If distance is shorter than v
            if ( v > dist[i])
            {
                //Update the distance and save the vertex
                v = dist[i];
                vertex = i;
            }
        }
    }
    //Return vertex with the shortest path
    return vertex;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{

    Heap<Edge> H; // min-heap by edges cost
    DSets D(size); //n trees with one node each
    Edge E;

    int counter = 0;
    int totalWeight = 0;

    //Build the heap with all the edges
    for (int v = 1; v <= size; v++)
    {
        //Create a node to the first element in the list at slot v
        Node *p = array[v].getFirst();
        //Create a node to the first element in the list at slot v
        while(p)
        {
            if (v < p->vertex)
            {
                //Insert edge
                H.insert(Edge(p->vertex, v, p->weight));
            }
            //Create a node to the first element in the list at slot v
            p = array[v].getNext();
        }
    }


    //
    while (counter < size - 1)
    {

        E = H.deleteMin(); //(v, u);
        //If the vertices are not the same
        if (D.find(E.head) != D.find(E.tail))
        {
            //Display
            display(E.tail, E.head, E.weight);
            //Join vertices
            D.join(D.find(E.head), D.find(E.tail));
            counter++;
            //Add weight to total weight
            totalWeight += E.weight;
        }
    }

    cout << "Total weight: " << totalWeight << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

void Graph::display(int v, int u, int weight) const
{
    cout << "(" << v << "," << u << "," << weight << ")" << endl;
}
