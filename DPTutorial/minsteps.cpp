#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <queue>

using namespace std;
using namespace std::chrono;
using

class DPSolver
{
public:
	DPSolver(int n)
		: d_number(n)
	{
		memo.assign(n+1, -1);
		dp.assign(n+1, -1);
	}
	
	int getRecursiveMinSteps(int n = -1)
	{
		if(n == -1)
			n = d_number;
		
		if(n == 1)
		{
			return 0;
		}
		
		int r = 1 + getMemoMinSteps(n-1);
		if(n%2 == 0) r = min(r, 1 + getMemoMinSteps(n/2));
		if(n%3 == 0) r = min(r, 1 + getMemoMinSteps(n/3));
		
		return r;
	}
	int getMemoMinSteps(int n = -1)
	{
		if(n == -1)
			n = d_number;
		
		if(n == 1)
		{
			return 0;
		}
		
		if(memo[n] != -1)
		{
			return memo[n];
		}
		
		int r = 1 + getMemoMinSteps(n-1);
		if(n%2 == 0) r = min(r, 1 + getMemoMinSteps(n/2));
		if(n%3 == 0) r = min(r, 1 + getMemoMinSteps(n/3));
		memo[n] = r;
		
		return r;
	}
	
	typedef queue<pair<int, int> > MemoQueue;
	typedef make_pair<int, int> makeResult;
	struct Frame
	{
		int ret;
		int idx;
		Frame(int x, int y)
			: ret(x), idx(y)
		{}
		
	};
	int getIterativeMemoMinSteps(int n)
	{
		memo.clear();
		memo.assign(n+1, -1);
		
		queue<int > memoQ;
		
		memoQ.push(n);
		while(!memoQ.empty())
		{
			int idx = memoQ.pop();
			if(idx == 1)
			{
				memo[idx] = 0;
			}
			else if(memo[idx] == -1)
			{
				memoQ.push(idx-1);
			}
			else
			{
				memoQ.push
			}
			
		}
	}
	
	int getDpMinSteps(int n)
	{
		dp[1] = 0;  // base/trivial case
		for(int i = 2; i <= n; ++i)
		{
			dp[i] = 1 + dp[i-1];
			if(i % 2 == 0)
				dp[i] = min(dp[i], 1 + dp[i/2]);
			if(i % 3 == 0)
				dp[i] = min(dp[i], 1+ dp[i/3]);
		}
		return dp[n];
	}
		
private:
	int d_number;
	std::vector<int> memo;
	std::vector<int> dp;
};
typedef chrono::high_resolution_clock timer;
typedef chrono::high_resolution_clock::time_point HRCT;
int main (int argc, char const *argv[])
{
	/* code */
	cout << "Enter a positive integer: ";
	string input;
	getline(cin, input);
	istringstream iStr(input);
	
	int num(0);
	if(iStr >> num && num > 0)
	{
		DPSolver dps(num);
		int recursive(0);
		int memo(0);
		int dp(0);
		
		cout << "Min steps to get from " << num << " to 1" << endl;
		HRCT recStart = timer::now();
		//recursive = dps.getRecursiveMinSteps(num);
		HRCT recFinish = timer::now();
		
		HRCT memostart = timer::now();
		//memo = dps.getMemoMinSteps(num);
		HRCT memofinish = timer::now();
		
		HRCT dpStart = timer::now();
		dp = dps.getDpMinSteps(num);
		HRCT dpFinish = timer::now();
		
		nanoseconds recursiveTime = chrono::duration_cast<nanoseconds>(recFinish - recStart);
		nanoseconds memoTime = chrono::duration_cast<nanoseconds>(memofinish - memostart);
		nanoseconds dpTime = chrono::duration_cast<nanoseconds>(dpFinish - dpStart);
		
		cout << "Recursive " << endl;
		cout << "Result: " << recursive << endl;
		cout << "Time: " << recursiveTime.count() <<endl;
		
		cout << "Memoization " << endl;
		cout << "Result: " << memo << endl;
		cout << "Time: " << memoTime.count() <<endl;

		cout << "Dynamic Programming " << endl;
		cout << "Result: " << dp << endl;
		cout << "Time: " << dpTime.count() << endl;
		
	}
	return 0;
}
