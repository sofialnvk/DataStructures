#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>

#include "BinarySearchTree.h"
#include "keyCount.h"

using namespace std;



//Test program 3: BiIterator
int main( )
{
    BinarySearchTree<keyCount> T;
    ifstream file("words.txt");
    
    if (!file)
    {
        cout << "couldn't open file words.txt" << endl;
        return 1;
    }
    
    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
    file.close();
    
    for(auto j: V1)
        T.insert( j );
    
    T.printTree();
    
    /**************************************/
    cout << "\nPHASE 1: contains\n\n";
    /**************************************/
    
    vector<string> V2 = { "airborne", "stop", "yelp", "Sweden", "obligations", "unbridled" };
    
    for(auto w: V2)
    {
        if( T.contains( w ) != T.end() ) //NOTE: contains should now return a bi-iterator
            cout << "\""<< w << "\"" << " in the tree" << endl;
        else
            cout << "\""<< w << "\"" << " not in the tree" << endl;
    }
    

    
    return 0;
}
