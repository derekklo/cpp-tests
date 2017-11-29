/* generic Visitor implementation */
#ifndef __GENERIC_VISITOR__
#define __GENERIC_VISITOR__

#include <typeinfo>
#include <cassert>
#include <iostream>

using namespace std;

class FooHost;
class BarHost;

class AcyclicVisitor
{
public:
	virtual ~AcyclicVisitor() {}
};

template <class T, class R = void>
class Visitor {
public:
	using ReturnType = R;
	virtual R Visit(T&)=0;
};

template <class... Ts>
class ConcreteVisitor
: public AcyclicVisitor
, public Visitor<Ts, void>...
{
	int _fooCount = 0;
	int _barCount = 0;
public:
	void Visit(FooHost& f) override
	{
		_fooCount += 1;
	}

	void Visit(BarHost& b) override
	{
		_barCount += 1;
	}

	int fooCount() { return _fooCount; }
	int barCount() { return _barCount; }
};

/* Visitable Interface */

#define DEFINE_VISITABLE() \
	virtual ReturnType Accept(AcyclicVisitor& guest) \
		override { \
		return this->AcceptImpl(*this, guest); \
	}

template <typename R = void>
class Visitable {
public:
	using ReturnType = R;
	virtual ~Visitable() {}
	virtual R Accept(AcyclicVisitor&)=0;

protected:
	template <class T>
	static R AcceptImpl(T& v, AcyclicVisitor& g)
	{
		assert(typeid(v) == typeid(T)
			&& "Please use DEFINE_VISITABLE");
		// Apply Acyclic Visitor
		if (auto p = dynamic_cast<Visitor<T, R>*>(&g)) {
			return p->Visit(v);
		}
		return R();
	}
};

#endif