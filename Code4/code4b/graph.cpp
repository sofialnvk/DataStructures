/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

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
    int *dist  = new int [size + 1];
    int *path  = new int [size + 1];
    bool *done  = new bool[size + 1];

    int start = 1;
    int totalWeight = 0;

    for(int v = 1; v<= size; v++)
    {
        dist[v] = INFINITY;
        path[v] = 0;
        done[v] = false;
    }
    dist[start] = 0; //start can be any vertex
    done[start] = true;
    int v = start;

    while (true)
    {
        Node *p = array[v].getFirst();
        //cout << p->vertex << endl;
        while(p)
        {
            int u = p->vertex;
            if ( done[u]==false && dist[u] > p->weight )
            {
                dist[u] = p->weight;
                path[u] = v;
            }
            p = array[v].getNext();
        }
        v = find_smallest_undone_distance_vertex(dist, done);
        if (v == 0) break; //exit the loop
        done[v] = true;
    }

}
int Graph::find_smallest_undone_distance_vertex(int dist[], bool done[]) const
{
    int v = INFINITY+1;
    int vertex = 0;

    for (int i = 1; i <=size; i++)
    {
        if (done[i]== false )
        {
            if ( v > dist[i])
            {
                v = dist[i];
                vertex = i;
            }
        }
    }
    return vertex;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{

    Heap<Edges> H; // min-heap by edges cost
    DSets D(size); //n trees with one node each

    //H.heapify(E); //build the heap with all edges

    //Psuedo code
    for each Edge(u,v,w) in the graph
        H.insert(Edge(u,v,w));


    int counter = 0;
    int v = 1; //start


    while (counter < size - 1)
    {
        Node *p = array[v].getFirst();
        int u = p->vertex;
        (v, u) = H.deleteMin();
        if (D.find(u) != D.find(v))
        {
            display(v, u, p->weight);
            D.union(D.find(u), D.find(v));
            counter++;
        }
    }
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
