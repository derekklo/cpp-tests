/* Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. 
You are asked to burst all the balloons. 
If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 
Here left and right are adjacent indices of i. 
After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

Given [3,2,1,5,8]
Return:

	nums = [3,2,1,8,5] --> [3,2,8,5] --> [3,8,5] --> [3,5] --> [5] --> []
	coins=   2*1*8      +   3*2*8     +   1*3*8   +  8*5*1  + 1*8*1
			  16        +     48      +     24    +   40    +   8   = 136
             2*1*8      +   3*2*8     +   3*8*5   +  1*3*5  +   5   = 204
*/

/*
This looks like a dynamic programming problem
The trick will be to identify the recursive subcomponent and the logic for selecting.
The base cases are nums.size <= 2
There is asymmetry on the edges because the 1* multipliers on either edge doesn't move.
1. Find the largest 3 numbers in the array, x, y, z.  We want these ones multiplied together.
2. The numbers between x & y form one subarray.  The numbers between y & z form another subarray.
3. For this subarray, find the largest middle number - we want this multiplied with x & y, or y & z.
4. Repeat this for each subarray.
*/
/* 	1 2 3 4
	2 1 3 4
	3 1 2 4
	
*/

#include <iostream>
#include <sstream>
#include <vector>
//#include <hashset>
#include <map>
#include <set>
#include <assert.h>
#include <functional>
#include <list>

using namespace std;

class BalloonBurst {	
private:
	void swap(vector<int>& nums, int a, int b)
	{
		assert(a < nums.size());
		assert(b < nums.size());
		
		int temp = nums[a];
		nums[a] = nums[b];
		nums[b] = temp;
	}
	
	template<typename F>
	void permutate (vector<int>& nums, int n, F& functor)
	{
		if (n == 1)
		{
			functor(nums);
		}
		else
		{
			for (int i = 0; i < n-1; ++i)
			{
				permutate(nums, n-1, functor);
				swap(nums, (n % 2 == 1) ? 0 : i, n-1);
			}
			permutate(nums, n-1, functor);
		}
	}
	
public:


	int maxCoins()
	{
		map<int,int, std::greater<int> > sortPos;
		for (int i = 0; i < balloons.size(); ++i)
		{
			// store the sorted position (highest to lowest) of the nums array.
			sortPos[balloons[i]] = i;
		}
		
		return 0;
	}
	
	template<typename F>
	int bruteForce(F& functor)
	{
		// there are n balloons to pop; order matters, so n! permutations
		// we can use this as a correctness test for the optimized format
		
		vector<int> burstOrder;
		for(int i = 0; i < balloons.size(); ++i)
		{
			burstOrder.push_back(i);
		}
		permutate(burstOrder, burstOrder.size(), functor);
		return 0;
	}
	
	BalloonBurst(const vector<int>& values)
		: balloons(values)
			{	}
	
private:
	vector<int> balloons;
};

// Functors for testing and output
struct PrintOrder
{
	void operator() (const vector<int>& nums)
	{
		for(vector<int>::const_iterator numItr(nums.begin());
			numItr != nums.end(); ++numItr)
		{
			cout << *numItr << " ";
		}
		cout << endl;
	}
};

struct Counter
{
	int counter;
	void operator() (const vector<int>& nums)
	{
		++counter;
	}
	void printCount() { cout << counter << endl; }
};

class CountCoins
{
	int burstAndCollectCoins(vector<int>& balloons, int pos)
	{
		assert(pos < balloons.size());
		
		// get the balloon coin count
		int burst, left, right;
		if(balloons[pos] != -1)
			burst = balloons[pos];
		else
			burst = 1;
		// Check to the left
		int leftPos = pos-1;
		while(balloons[leftPos] == -1 && leftPos >= 0)
			--leftPos;
		left = (balloons[leftPos] != -1 && leftPos>=0) ? balloons[leftPos] : 1;
		// check to the right
		int rightPos = pos+1;
		while(balloons[rightPos] == -1 && rightPos<balloons.size())
			++rightPos;
		right = (balloons[rightPos] != -1 && rightPos<balloons.size()) ? balloons[rightPos] : 1;
		
//		cout << left << "*" << burst << "*" << right;
//		if(leftPos >= 0 || rightPos < balloons.size())
//			cout << " + ";
		
		// remove the balloon by setting it to -1;
		balloons[pos] = -1;
		return left*burst*right;
	}
	
public:
	CountCoins(const vector<int>& balloons)
		: origBalls(balloons), numBalls(balloons.size()) 
			{	}
	
	void operator() (const vector<int>& order)
	{
		// each iteration represents the order to burst balloons
		int sum = 0; // find the sum for this burst order and compare to maxCoins
		
		vector<int> balloons(origBalls);
		for(vector<int>::const_iterator oItr(order.begin());
			oItr != order.end(); ++oItr)
		{
			sum += burstAndCollectCoins(balloons, *oItr);
		}
//		cout << " = " << sum << endl;
		if(sum > maxCoins)
			maxCoins = sum;
	}
	
	int getMax() { return maxCoins; }
	
private:
	int maxCoins;
	int numBalls;
	vector<int> origBalls;
};


int main (int argc, char const *argv[])
{
	vector<int> balloons;
	std::string input;
	cout << "Enter a series of balloon values separated by spaces:";
	if(getline(cin, input))
	{
		istringstream iss(input);
		int num;
		while(iss >> num)
		{
			assert(num > 0);
			balloons.push_back(num);
		}
	}
	
//	cout << "TEST -- Print out all permutations" << endl;
//	BalloonBurst printTest(balloons);
//	PrintOrder p;
//	printTest.bruteForce(p);
	
	cout << "\nTEST -- Count up all permutations" << endl;
	BalloonBurst countTest(balloons);
	Counter c;
	countTest.bruteForce(c);
	c.printCount();
	
	cout << "\nTEST -- Find the max coins" << endl;
	BalloonBurst maxTest(balloons);
	CountCoins cc(balloons);
	maxTest.bruteForce(cc);
	cout << "Max Coins: " << cc.getMax() << endl;
	
	return 0;
}
