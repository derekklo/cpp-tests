#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>

class GroupSRMDiv2
{
public:
	GroupSRMDiv2();
	static int findGroups(std::vector<int>& t);
	
private:
	
};

GroupSRMDiv2::GroupSRMDiv2()
{
	
}

int GroupSRMDiv2::findGroups(std::vector<int>& t)
{
	// Create a hash of member-desired group sizes
	// Iterating through t, members requesting a particular group size will increment the corresponding bucket in the hash
	// At the end of t, check if each group size slot value (number of members requesting that size) is divisible by its key (group size requested)
	
	std::unordered_map<int, int> groupMap;
	
	for(int i=0; i < t.size(); ++i)
	{
		assert(t[i]>=1 && t[i]<=500);
		
		groupMap[t[i]] += 1;
	}
	
	// Number of groups is the sum of all the quotients, assuming all groups sizes divide evenly into the number of members requesting the respective size.
	int numGroups = 0;
	for(std::unordered_map<int, int>::const_iterator gItr(groupMap.begin());
		gItr != groupMap.end(); ++gItr)
	{
		if(gItr->second % gItr->first != 0)
		{
			return -1;
		}
		else
		{
			numGroups += gItr->second/gItr->first;
		}
	}
	
	return numGroups;
}

int main(int argc, const char* argv[])
{
	std::vector<int> members;
	std::string input;
	std::cout << "Enter members of t separated by spaces:";
	if(getline(std::cin, input))
	{
		std::istringstream iss(input);
		int groupsize;
		while(iss >> groupsize)
		{
			members.push_back(groupsize);
		}
		std::cout << GroupSRMDiv2::findGroups(members) << std::endl;
	}
	return 0;
}