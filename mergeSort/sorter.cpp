#include <iostream>
#include <ctime>
#include <cstdlib>

#include <chrono>
using namespace std::chrono;

using std::cout;
using std::cerr;
using std::endl;

class Sort
{
public:
	Sort(int* array, size_t numElements);
	virtual ~Sort();
	void TopDownMergeSort(int* b, size_t begin, size_t end, int* a);
	void MergeSort();
	
	void QuickSort();
	void QuickSortHelper(int* a, int begin, int end);
	int Partition(int* a, int begin, int end);
	
	void print();
	
private:
	size_t _n;
	int* _a;
	int* _b;
	
	void createCopyArray(int** a, int** b, int n);
	void SortAndMerge(int* a, size_t begin, size_t mid, size_t end, int* b);
};

Sort::Sort(int* array, size_t numElements)
	: _n(numElements), _a(array), _b(0)
{
	createCopyArray(&_a, &_b, _n);
/*
	cerr << "_a: ";
	for (int i=0; i<_n; ++i)
	{
		cerr << _a[i] << " ";
	}
	cerr << endl;
	cerr << "_b: ";
	for (int j=0; j<_n; ++j)
	{
		cerr << _b[j] << " ";
	}
	cerr << endl;
*/
}

Sort::~Sort()
{
	if(_b) 
		delete _b;
}

void Sort::createCopyArray(int** a, int** b, int n)
{
	*b = new int[n];
	for(int i=0; i<n; ++i)
	{
		(*b)[i] = (*a)[i];
	}
	cerr << "Copy: ";
	for (int j=0; j<n; ++j)
	{
		cerr << (*b)[j] << " ";
	}
	cerr << endl;
}

void Sort::SortAndMerge(int* b, size_t begin, size_t mid, size_t end, int* a)
{
//	cerr << "SortAndMerge: " << begin << " " << mid << " " << end << endl;
	int i = begin, j = mid;
	
	for(int x=begin; x < end; ++x)
	{
//		cerr << b[x] << " ";
	}
//	cerr << endl;
	
	for(int k = begin; k < end; ++k)
	{
		if(i < mid && (j >= end || b[i] <= b[j]))
		{
//			cerr << "a[" << k << "]=bi[" << i << "]=" << b[i] << endl;
			a[k] = b[i++];
		}
		else 
		{
//			cerr << "a[" << k << "]=bj[" << j << "]=" << b[j] << endl;
			a[k] = b[j++];
		}
	}
}

void Sort::TopDownMergeSort(int* b, size_t begin, size_t end, int* a)
{
	// recursively split b into individual elements, then merge them in sorted order
	// recursive base case
	
//	cerr << "TopDownMergeSort: " << begin << " " << end << endl;
	/*
	for(int i = 0; i < _n; ++i)
	{
		cerr << _b[i] << " ";
	}
	cerr << endl;
	*/
	if(end - begin < 2)
	{
//		cerr << "return" << endl;
		return;
	}
	
	// split and call recursion
	int iMid((begin + end) / 2);
	TopDownMergeSort(a, begin, iMid, b);
	TopDownMergeSort(a, iMid, end, b);
	
	// sorting section
	SortAndMerge(b, begin, iMid, end, a);
}

void Sort::MergeSort()
{
//	cerr << "here 1" << endl;
	TopDownMergeSort(_b, 0, _n, _a);
}

int Sort::Partition(int* a, int begin, int end)
{
	int pivot = a[begin];
	int i = begin - 1;
	int j = end + 1;
	while(1)
	{
		do
		{
			++i;
		} while(a[i] < pivot);
		do
		{
			--j;
		} while(a[j] > pivot);
		
		if(i >= j)
		{
			return j;
		}
		/*
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		*/
		a[i] ^= a[j];
		a[j] ^= a[i];
		a[i] ^= a[j];
	}
}

void Sort::QuickSortHelper(int* a, int begin, int end)
{
	if(begin < end)
	{
		int pindex = Partition(a, begin, end);
		QuickSortHelper(a, begin, pindex);
		QuickSortHelper(a, pindex+1, end);
	}
}

void Sort::QuickSort()
{
	QuickSortHelper(_a, 0, _n);
}

void Sort::print()
{
	cout << "Post-Sort: ";
	for(int i = 0; i < _n; ++i)
	{
		std::cout << _a[i] << " ";
	}
	std::cout << std::endl;
}

void randomPopulate(int* elements, int n)
{
	srand(time(NULL));
	cout << "Pre-Sort: ";
	for(int i=0; i < n; ++i)
	{
		elements[i] = rand() % 10000;
		cout << elements[i] << " ";
	}
	cout << endl;
}

int main(int argc, char** argv)
{
//	std::cout << "Enter number of elements:";
	std::string input;
	int numElems = 999;
	int elements[numElems];
	
	randomPopulate(elements, numElems);
	
	Sort* mySort = new Sort(elements, numElems);
	auto start1 = steady_clock::now();
	mySort->MergeSort();
	auto stop1 = steady_clock::now();
	duration<double> elapsed_time1 = duration_cast<duration<double> >(stop1 - start1);
	cout << "Mergesort time: " << 1000* elapsed_time1.count() << " milliseconds." << endl;
	mySort->print();
	
	randomPopulate(elements, numElems);
	
	Sort* qSort = new Sort(elements, numElems);
	auto start2 = steady_clock::now();
	qSort->QuickSort();
	auto stop2 = steady_clock::now();
	duration<double> elapsed_time2 = duration_cast<duration<double> >(stop2 - start2);
	cout << "Quicksort time: " << 1000* elapsed_time2.count() << " milliseconds." << endl;
	qSort->print();
	
/*
	if(std::getline(std::cin, input))
	{
		std::istringstream instr(input);
		instr >> numElems;
	}
	std::cout << "Enter elements separated by spaces or hit Enter for random generator:";
	int elements[numElems];
	if(std::getline(std::cin, input))
	{
		
	}
*/
}