#include <iostream>
#include <vector>
#include <algorithm>  //std::rotate
#include <iterator>
#include <fstream>
#include <iomanip>
//Added
using namespace std;

/****************************************
* Declarations                          *
*****************************************/

using Test = bool(*)(int);

//Generic class to write an item of type T to a stream
template<typename T>
class Formatter
{
public:

	Formatter(std::ostream& os, int width, int per_line)
		: os_(os), per_line_(per_line), width_(width)
	{}

	void operator()(const T& t)
	{
		os_ << std::setw(width_) << t;
		if (++outputted_ % per_line_ == 0)
			os_ << "\n";
	}

private:
	std::ostream&  os_;		//output stream
	const int per_line_;	//number of columns per line
	const int width_;		//column width
	int   outputted_{ 0 };	//counter of number of items written to os_
};


//Divide-and-conquer algorithm
//IMPLEMENT
void stable_partition(vector<int>& V, Test p);

//Iterative algorithm
//IMPLEMENT
void stable_partition_iterative(vector<int>& V, Test p);

void execute(vector<int>& V);

bool even(int i);


/****************************************
* Main                                  *
*****************************************/

int main()
{
	/*****************************************************
	* TEST PHASE 1                                       *
	******************************************************/
	cout << "TEST PHASE 1\n\n";

	vector<int> seq1{ 1, 2 };

	cout << "Sequence: ";
	copy(seq1.begin(), seq1.end(), ostream_iterator<int>(cout, " "));

	execute(seq1);

	/*****************************************************
	* TEST PHASE2                                        *
	******************************************************/
	cout << "\n\nTEST PHASE 2\n\n";

	vector<int> seq2{ 2 };

	cout << "Sequence: ";
	copy(seq2.begin(), seq2.end(), ostream_iterator<int>(cout, " "));

	execute(seq2);

	/*****************************************************
	* TEST PHASE3                                        *
	******************************************************/
	cout << "\n\nTEST PHASE 3\n\n";

	vector<int> seq3;

	cout << "Sequence: empty";

	execute(seq3);

	/*****************************************************
	* TEST PHASE 4                                       *
	******************************************************/
	cout << "\n\nTEST PHASE 4\n\n";

	vector<int> seq4{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	cout << "Sequence: ";
	copy(seq4.begin(), seq4.end(), ostream_iterator<int>(cout, " "));

	execute(seq4);

	/*****************************************************
	* TEST PHASE4                                        *
	******************************************************/
	cout << "\n\nTEST PHASE 4: test with long sequence loaded from a file\n\n";

	ifstream file("test_data.txt");

	if (!file)
	{
		cout << "Could not open test data file!!\n";
		return 0;
	}

	vector<int> seq5;

	istream_iterator<int> in_itr(file);
	istream_iterator<int> in_itr_end;

	//read the data in the file into seq5
	copy(in_itr, in_itr_end, back_inserter(seq5));

	cout << "Number of items in the sequence: " << seq5.size() << endl;

	vector<int> seq6(seq5);

	cout << "\n After stable partition ..." << endl;

	stable_partition_iterative(seq5, even);

	stable_partition(seq6, even); //recursive

	if ( std::equal(begin(seq5), end(seq5), begin(seq6)) )
	{
		//Display
		std::for_each(begin(seq6), end(seq6), Formatter<int>(cout, 8, 5));
	}
	else
	{
		cout << "Error: recursive and iterative algorithms give different results!!" << endl;
	}

	cout << endl;

	return 0;
}

/****************************************
* Functions definitions                 *
*****************************************/

bool even(int i)
{
	return i % 2 == 0;
}


//Divide-and-conquer algorithm
vector<int>::iterator stable_partition(vector<int>& V, vector<int>::iterator first, vector<int>::iterator last, Test p)
{	
	// n: number of values in the sequence
    int n = last-first;
    //Base cases
    //Empty sequence
    if (n == 0)
    {
        return first;
    }
    //One element sequence
    if (n == 1)
    {
        //If bool is true, if element is "green"
        if (p(*first))
        {
            return last;
        }
        //If bool is false, if element is not "green"
        else
        {
            return first;
        }
    }

	//Points to the middle element
    vector<int>::iterator mid = first + (n/2);

    vector<int>::iterator vLeft = stable_partition(V, first, mid, p);
    vector<int>::iterator vRight = stable_partition(V, mid, last, p);

	//Rotates to create stable partition
	//vLeft --> mid = first section
	//mid --> vRight = second section
	//These sections switch places (rotate)
    vector<int>::iterator it = rotate(vLeft,mid,vRight);

    return it;

}

void stable_partition(vector<int>& V, Test p)
{
	stable_partition(V, begin(V), end(V), p);
}

//Iterative algorithm
void stable_partition_iterative(vector<int>& V, Test p)
{
    int i = 0;

	vector<int>::iterator it;

    //If bool is true, values are placed in this vector
    vector<int> left;
    //If bool is false, values are placed in this vector
    vector<int> right;

    for (it = V.begin(); it<V.end(); ++it, ++i)
    {
        //If bool is true
        if(p(V[i]))
        {
            left.push_back(*it);
        }
        else
        {
            right.push_back(*it);
        }
    }
    //Add the right vector to the end of the left vector
    left.insert(left.end(), right.begin(), right.end());
    //Replace the vector V with the "sorted" vector
    V.swap(left);
}

void execute(vector<int>& V)
{
	vector<int> _copy(V);

	cout << "\nIterative stable partition: ";
	stable_partition_iterative(V, even);

	//Display
	std::copy(begin(V), end(V), ostream_iterator<int>(cout, " "));

	cout << "\nDivide-and-conquer stable partition: ";
	stable_partition(_copy, even);

	//Display
	std::copy(begin(_copy), end(_copy), ostream_iterator<int>(cout, " "));
}
