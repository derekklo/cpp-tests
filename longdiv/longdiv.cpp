#include <iostream>
#include <string>
#include <sstream>

int divideInt(int dividend, int divisor)
{
	int sign = 1;
	if(dividend < 0)
	{
		dividend *= -1;
		sign *= -1;
	}
	if(divisor < 0)
	{
		divisor *= -1;
		sign *= -1;
	}
	
	int quotient=0, curBit=1;
	
	while(dividend >= divisor)
	{
		divisor <<= 1;
		curBit <<= 1;
	}
	
	// we intentionally go past tgt by 1 digit so backtrack
	divisor >>= 1;
	curBit >>= 1;
	
	while(curBit != 0)
	{
		if(dividend >= divisor)
		{
			quotient |= curBit;
			dividend -= divisor;
		}
		divisor >>= 1;
		curBit >>= 1;
	}
	return sign * quotient;
}

int main()
{
	std::string input;
	int divd=0, divr=1, q=0;
	std::cout << "Enter [dividend] [divisor]:";
	getline(std::cin, input);
	std::istringstream is(input);
	is >> divd;
	is >> divr;
	q = divideInt(divd, divr);
	std::cout << divd << " / " << divr << " = " << q << std::endl;
}