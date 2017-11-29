#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
using std::vector;

class DPCoins
{
public:	
	int minCoins(int sum, vector<int> values);
private:
	int min(int x, int y) { return x <= y ? x : y; }
	
	/* data */
};

int DPCoins::minCoins(int sum, vector<int>values)
{
	const static int BIGINT = std::numeric_limits<int>::max();
	int n = values.size();
	vector<int> mins(sum+1, BIGINT);
	mins[0] = 0;
	for(int i=1; i <= sum; ++i)
	{
		for(int j=0; j < n; ++j)
		{
			std::cerr << i << ", " << j << ", " << values[j] 
				<< ", " << mins[i-values[j]] << ", " << mins[i];
			if(values[j] <= i)
			{
				int step = mins[i-values[j]];
				if(step != BIGINT && step+1 < mins[i])
				{
					mins[i] = step +1;
				}
			}
			std::cerr << " : " << mins[i] << std::endl;
		}
	}
	return mins[sum];
}

int main(int argc, const char* argv[])
{
	std::string input;
	vector<int> coinValues;
	int sum;
	std::cout << "Enter coin values separated by spaces:";
	if(getline(std::cin, input))
	{
		std::istringstream inStr(input);
		int val;
		while(inStr >> val)
		{
			coinValues.push_back(val);
		}
	}
	std::cout << "Enter desired sum:";
	if(getline(std::cin, input))
	{
		std::istringstream inStr(input);
		if(inStr >> sum)
		{
			DPCoins dp;
			std::cout << dp.minCoins(sum, coinValues) << std::endl;
		}
	}
	return 0;
}