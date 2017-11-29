#include "genericvisitor.h"
#include "visitableHost.h"
#include <vector>
#include <iostream>


int main (int argc, char** argv)
{
	std::vector<VHost*> hosts;
	hosts.push_back(new FooHost());
	hosts.push_back(new BarHost());
	hosts.push_back(new FooHost());

	ConcreteVisitor<FooHost, BarHost> cv;

	for (auto i(hosts.begin()); i != hosts.end(); ++i)
	{
		(*i)->Accept(cv);
	}
	std::cout << cv.fooCount() << ":" << cv.barCount() << std::endl;

}