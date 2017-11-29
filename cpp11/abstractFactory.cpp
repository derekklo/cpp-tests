/* Factory lab */
// auto ....() -> decltype() // lambda

#include <map>
#include <functional>
#include <memory>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

class Foo 
{
public:
	virtual void print() = 0;
	Foo();
	Foo(int x);
	virtual ~Foo();
};

class FooA : public Foo
{
public:
	void print()
	{
		cout << "I am FooA:" << _id;
	}
	FooA() : _id(-1) {}
	FooA(int x): _id(x) {}
	 ~FooA();

protected:
	int _id;
};

class FooB : public Foo
{
public:
	void print()
	{
		cout << "I am FooB:" << _id;
	}
	FooB() : _id(-1) {}
	FooB(int x): _id(x) {}
	~FooB();

protected:
	int _id;
};

enum class FooType 
{
	A = 0,
	B = 1,
	C = 2,
	total
};

template <typename IdentifierType,
	typename ProductCreator>
class Factory
{
private:
	//typedef decltype(ProductCreator()()) Product;

public:
	bool Register(const IdentifierType& id,
		ProductCreator creator)
	{
		return map_.emplace(id, creator).second;
	}
	
	bool Unregister(const IdentifierType& id) 
	{
		return map_.erase(id) == 1;
	}

	auto CreateObject(const IdentifierType& id)
	{
		auto i = map_.find(id);
		if(i!= map_.end()) {
			return (i->second)();
		}
		return
			decltype((i->second)())();
	}
	// passing constructor arguments
	template < typename... Args>
	auto CreateObject(const IdentifierType& id,
		Args&&... args)
	{
		auto i = map_.find(id);
		if(i != map_.end()) {
			return (i->second)(std::forward<Args>(args)...);
		}
		return
			decltype((i->second)(std::forward<Args>(args)...))();
	}

private:
	std::map<IdentifierType,ProductCreator> map_;
};

int main(int argc, char** argv)
{
	Factory <FooType, std::function<unique_ptr<Foo>(int)> > plant;
	plant.Register(FooType::A, [](int x) {return new FooA(x);});
}




