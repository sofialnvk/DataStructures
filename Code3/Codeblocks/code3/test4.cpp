/* ************************** TEST 1 ******************************** */

#include <iostream>
#include <vector>

#include "BinarySearchTree.h"

using namespace std;

// Test program 1: get_parent
int main( )
{
    BinarySearchTree<int> t1;

    vector<int> V = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

    /**************************************/
    cout << "PHASE 0: insert\n\n";
    /**************************************/

    for(auto j: V)
        t1.insert( j );

    //Display the tree
    cout << "T1" << endl;
    t1.printTree( );
    cout << endl;


    /**************************************/
    cout << "\nPHASE 1: findMin, FindMax\n\n";
    /**************************************/

    cout << "Min = " << t1.findMin( ) << endl;
    cout << "Max = " << t1.findMax( ) << endl;

    /**************************************/
    cout << "\nPHASE 2: contains\n\n";
    /**************************************/

    for(int i = 2; i < 36; i+=2 )
    {
        if ( t1.contains(i) )
            cout << i << " in the tree" << endl;
        else
            cout << i << " not in the tree" << endl;
    }

    /**************************************/
    cout << "\nPHASE 3: copy constructor\n\n";
    /**************************************/

    BinarySearchTree<int> t2(t1);

    //Display the tree
    cout << "T2" << endl;
    t2.printTree( );
    cout << endl;


    /**************************************/
    cout << "\nPHASE 4: makeEmpty\n\n";
    /**************************************/

    t2.makeEmpty();

    //Display the tree
    cout << "T2" << endl;
    t2.printTree( );
    cout << endl;

    /**************************************/
    cout << "\nPHASE 5: operator=\n\n";
    /**************************************/

    t2 = t1;

    //Display the tree
    cout << "T2" << endl;
    t2.printTree( );
    cout << endl << endl;


    /**************************************/
    cout << "\nPHASE 6: get_parent\n\n";
    /**************************************/

    cout << "Parent of node 14: "
         << t2.get_parent(14) << endl;

    cout << "Parent of node 10: "
         << t2.get_parent(10) << endl;

    cout << "Parent of node 33: "
         << t2.get_parent(33) << endl;

    cout << "Parent of node 20: "
         << t2.get_parent(20) << endl;

    cout << "Parent of node 28: "
         << t2.get_parent(28) << endl;


    /**************************************/
    cout << "\nPHASE 7: remove\n\n";
    /**************************************/

    for(int i = 0; i < 35; i+= 2 )
    {
        cout << "remove " << i << endl;
        t1.remove( i );
    }

    //Display the tree
    cout << "\nT1" << endl;
    t1.printTree( );
    cout << endl;

    cout << "\nFinished testing" << endl;

    return 0;
}



/* ****************************** TEST 2 *************************** */

//#include <iostream>
//#include <vector>
//
//#include "BinarySearchTree.h"
//
//using namespace std;
//
//
//
//// Test program 2
//int main( )
//{
//    BinarySearchTree<int> t1;
//
//    vector<int> V = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};
//
//    /**************************************/
//    cout << "PHASE 0: insert\n\n";
//    /**************************************/
//
//    for(auto j: V)
//        t1.insert( j );
//
//    //Display the tree
//    cout << "T1" << endl;
//    t1.printTree( );
//    cout << endl;
//
//    /**************************************/
//    cout << "\nPHASE 1: findMin, FindMax\n\n";
//    /**************************************/
//
//    cout << "Min = " << t1.findMin( ) << endl;
//    cout << "Max = " << t1.findMax( ) << endl;
//
//    /**************************************/
//    cout << "\nPHASE 2: contains\n\n";
//    /**************************************/
//
//    for(int i = 2; i < 36; i+=2 )
//    {
//        if ( t1.contains(i) )
//            cout << i << " in the tree" << endl;
//        else
//            cout << i << " not in the tree" << endl;
//    }
//
//    /**************************************/
//    cout << "\nPHASE 3: copy constructor\n\n";
//    /**************************************/
//
//    BinarySearchTree<int> t2(t1);
//
//    //Display the tree
//    cout << "T2" << endl;
//    t2.printTree( );
//    cout << endl;
//
//    /**************************************/
//    cout << "\nPHASE 4: makeEmpty\n\n";
//    /**************************************/
//
//    t2.makeEmpty();
//
//    //Display the tree
//    cout << "T2" << endl;
//    t2.printTree( );
//    cout << endl;
//
//    /**************************************/
//    cout << "\nPHASE 5: operator=\n\n";
//    /**************************************/
//
//    t2 = t1;
//
//    //Display the tree
//    cout << "T2" << endl;
//    t2.printTree( );
//    cout << endl << endl;
//
//
//    /**************************************/
//    cout << "\nPHASE 6: remove\n\n";
//    /**************************************/
//
//    for(int i = 0; i < 35; i+= 2 )
//    {
//        cout << "remove " << i << endl;
//        t1.remove( i );
//    }
//
//    //Display the tree
//    cout << "\nT1" << endl;
//    t1.printTree( );
//    cout << endl;
//
//    /**************************************/
//    cout << "\nPHASE 7: find_pred_succ\n\n";
//    /**************************************/
//
//     //Display the tree
//    cout << "T2" << endl;
//    t2.printTree( );
//    cout << endl << endl;
//
//    int low = 15, high = 15;
//    t2.find_pred_succ(15, low, high);
//    cout << low << " < " << 15 << " < " << high << endl;
//
//    low = 13, high = 13;
//    t2.find_pred_succ(13, low, high);
//    cout << low << " < " << 13 << " < " << high << endl;
//
//    low = 28, high = 28;
//    t2.find_pred_succ(28, low, high);
//    cout << low << " < " << 28 << " < " << high << endl;
//
//    low = high = 12;
//    t2.find_pred_succ(12, low, high);
//    cout << low << " < " << 12 << " < " << high << endl;
//
//    low = high = 35;
//    t2.find_pred_succ(35, low, high);
//    cout << low << " < " << 35 << " < " << high << endl;
//
//    low = high = 5;
//    t2.find_pred_succ(5, low, high);
//    cout << low << " < " << 5 << " < " << high << endl;
//
//    cout << "\nFinished testing" << endl;
//
//    return 0;
//}


/* ******************************* TEST 3 ************************** */

//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <fstream>
//#include <string>
//
//#include "BinarySearchTree.h"
//
//using namespace std;
//
//
//
// //Test program 3: BiIterator
//int main( )
//{
//    BinarySearchTree<string> T;
//    ifstream file("words.txt");
//
//    if (!file)
//    {
//        cout << "couldn't open file words.txt" << endl;
//        return 1;
//    }
//
//    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
//    file.close();
//
//    for(auto j: V1)
//        T.insert( j );
//
//    /**************************************/
//    cout << "\nPHASE 1: contains\n\n";
//    /**************************************/
//
//    vector<string> V2 = { "airborne", "stop", "yelp", "Sweden", "obligations", "unbridled" };
//
//    for(auto w: V2)
//    {
//        if( T.contains( w ) != T.end() ) //NOTE: contains should now return a bi-iterator
//            cout << "\""<< w << "\"" << " in the tree" << endl;
//        else
//            cout << "\""<< w << "\"" << " not in the tree" << endl;
//    }
//
//
//    /**************************************/
//    cout << "\nPHASE 2: BiIterator, operator++\n\n";
//    /**************************************/
//
//    for(BinarySearchTree<string>::BiIterator it = T.begin(); it != T.end(); ++it)
//    {
//        cout << *it << endl;
//    }
//
//    cout << endl;
//
//    /**************************************/
//    cout << "PHASE 3: BiIterator, operator--\n\n";
//    /**************************************/
//
//    string largest = T.findMax( );
//
//    for(auto it = T.contains( largest ); it != T.end(); --it)
//    {
//        cout << *it << endl;
//    }
//
//    cout << "\nFinished testing" << endl;
//
//    return 0;
//}




/* *************************  TEST 4 ******************************* */
//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <fstream>
//
//#include "BinarySearchTree.h"
//
//using namespace std;
//
////Test program 4: BiIterators and remove
//int main( )
//{
//	BinarySearchTree<int> t1;
//
//    vector<int> V = { 8, 3, 10, 1, 6, 14, 4, 7, 13};
//
//	/**************************************/
//	cout << "PHASE 0: insert\n\n";
//	/**************************************/
//
//	//Create the tree shown in exercise 3 of lab 3
//	for(auto j: V)
//		t1.insert( j );
//
//	//Display the tree
//	cout << "T1" << endl;
//	t1.printTree( );
//	cout << endl;
//
//	/**************************************/
//	cout << "PHASE 3: BiIterator and remove\n\n";
//	/**************************************/
//
//	BinarySearchTree<int>::BiIterator it1 = t1.contains(3);
//	BinarySearchTree<int>::BiIterator it2 = t1.contains(4);
//
//	cout << "*it1 = " << *it1 << endl;
//	cout << "*it2 = " << *it2 << endl;
//
//	cout << "Remove 3 ..." << endl;
//
//	t1.remove(3);
//
//	cout << "*it1 = " << *it1 << endl; //iterator it1 should be invalidated!
//	cout << "*it2 = " << *it2 << endl; //iterator it2 should still point to 4
//
//	cout << "\nFinished testing" << endl;
//
//	t1.printTree();
//
//	return 0;
//}


/* ********************************** TEST 5 ************************************ */

//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <fstream>
//#include <string>
//
//#include "BinarySearchTree.h"
//#include "keyCount.h"
//
//using namespace std;
//
//
//
////Test program 3: BiIterator
//int main( )
//{
//    BinarySearchTree<keyCount> T;
//    ifstream file("words.txt");
//
//    if (!file)
//    {
//        cout << "couldn't open file words.txt" << endl;
//        return 1;
//    }
//
//    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
//    file.close();
//
//    for(auto j: V1)
//        T.insert( j );
//
//    T.printTree();
//
//
//    return 0;
//}

