/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/
//digraph1.txt

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    //Create queue
    Queue<int> Q;

    //Initialize all distances and paths
    for(int v = 1; v<= size; v++)
    {
        dist[v]=INFINITY;
        path[v]=0;
    }

    //Set distance of start vertex to 0
    dist[s]=0;
    //Add start value to queue
    Q.enqueue(s);

    while(!Q.isEmpty())
    {
        //Save the first value in the queue in v
        int v = Q.getFront();
        //Create a node to the first element in the list at slot v
        Node *p = array[v].getFirst();
        Q.dequeue(); //Remove from queue

        //Loop through the list
        while(p)
        {
            int u = p->vertex;
            //Change initialized value
            //The elements that have not been visited are marked with infinity
            if(dist[u]==INFINITY)
            {
                //Update distance and path
                dist[u]=dist[v]+1;
                path[u]=v;
                //Add u to the list
                Q.enqueue(u);
            }
            //Point to the next value in the list
           p = array[v].getNext();
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    //Initialize all distances and paths
    for (int v = 1; v<= size; v++)
    {
        dist[v]=INFINITY;
        path[v]=0;
        //Done is used to mark the visited elements
        done[v]=false;
    }
    //Set distance of start vertex to 0
    //Start vertex is visited, therefore done = true
    dist[s]=0;
    done[s]=true;
    //Copy start value to v
    int v = s;

    while(true)
    {
        //Create a node to the first element in the list at slot v
        Node *p = array[v].getFirst();
        //Loop through the list
        while(p)
        {
            int u = p->vertex;
            //Change initialized value
            //Only change value if it has not been visited and if there is a cheaper path
            if(done[u]==false && dist[u] > dist[v] + p->weight)
            {
                dist[u]=dist[v]+p->weight;
                path[u]=v;
            }
            //Point to the next value in the list
            p = array[v].getNext();
        }

        //Finds the vertex with the shortest path that has not been visited
        v=find_smallest_undone_distance_vertex();
        //If no vertex was found they have all been visited, break the loop
        if(v==0)
        {
            //exit the loop
            break;
        }
        done[v]=true; //Mark the found vertices with true
    }
}

int Digraph::find_smallest_undone_distance_vertex() const
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

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    printHelp(t);
    cout << " (" << dist[t] <<") " << endl;

}

void Digraph::printHelp(int t) const{
    if(path[t] != 0){
        printHelp(path[t]);
    }
    cout << " " << t << " ";
}
