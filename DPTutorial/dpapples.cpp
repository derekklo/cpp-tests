#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <exception>

using namespace std;

class VerboseException : std::exception
{
public:
	explicit VerboseException(const std::string& info) _NOEXCEPT;
	virtual ~VerboseException() _NOEXCEPT { }
	const char* what() const _NOEXCEPT { return whatStr.c_str(); }
	
private:
	std::string whatStr;
};

VerboseException::VerboseException(const std::string& info) _NOEXCEPT
	: whatStr(info)
		{ }

class DPApples
{
public:
	int maxApples(int n, int m, vector< vector<int> >& mtx);

private:
	int max(int x, int y) { return x >= y ? x : y; }
};

int DPApples::maxApples(int n, int m, vector< vector<int> >& mtx)
{
	vector< vector<int> > sums;
	cerr << "debug1" << endl;
	for (int i=0; i < n; ++i)
	{
		sums.push_back(vector<int>(m, 0));
	}
	cerr << "debug2" << endl;
	for( int i=0; i < n; ++i)
	{
		for( int j=0; j < m; ++j)
		{
			cout << mtx[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int i = 0; i < n; ++i)
	{
		for( int j=0; j < m; ++j)
		{
			sums[i][j] = mtx[i][j] + max((i-1 >= 0 ? sums[i-1][j] : 0),(j-1 >= 0 ? sums[i][j-1] : 0));
			cout << sums[i][j] << " ";
		}
		cout << endl;
	}
	return sums[n-1][m-1];
}


int main(int argc, const char* argv[])
{
	string input;
	int n=0, m=0;
	vector< vector<int> > table;
	
	cout << "Enter x and y dimensions for table separated by spaces:";
	if(getline(cin, input))
	{
		istringstream iss(input);
		if(iss >> n && iss >> m)
		{
			if (n<0 || m<0)
				return 0;
			
			bool rdm(true);
			cout << "Do you want to pick a table at random? (y/n):";
			if(getline(cin, input))
			{
				if (input == "n")
				{
					rdm = false;
				}
			}
			
			if(rdm)
			{
				cout << "Selecting table at random." << endl;
				srand(time(NULL));
				cerr << "debug3" << endl;
				for (int i=0; i < n; ++i)
				{
					table.push_back(vector<int>());
					for (int j=0; j < m; ++j)
					{
						cerr << "debug4" <<endl;
						table[i].push_back(rand() % 50 + 1);
					}
				}
				cerr << "debug5" << endl;
			}
			else
			{
				int i=0;
				while (i < n)
				{
					cout << "Enter " << m << " numbers separated by spaces:";
					try
					{
						if(getline(cin, input))
						{
							int val;
							iss.str(input);
							while (iss >> val)
							{
								if(val > 0)
								{
									table[i].push_back(val);
								}
								else
								{
									throw VerboseException("Numbers must be greater than 0!");
								}
							}
						}
					}
					catch(exception& e)
					{
						cout << e.what() << endl;
						continue;
					}
					
					++i;
				}
			}
		}
		
		DPApples dp;
		cout << "\n" << dp.maxApples(n, m, table) << endl;
	}
}