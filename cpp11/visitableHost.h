#include "genericvisitor.h"

class VHost
: public Visitable<void>
{
};

class FooHost 
: public VHost
{
public:
	DEFINE_VISITABLE()

	const char* name() { return "Foo"; }
};

class BarHost 
: public VHost
{
public:
	DEFINE_VISITABLE()

	const char* name() { return "Bar"; }
};
