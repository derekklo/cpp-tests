#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

class Processor;
class Creator;

enum SelectionId { 
	GETDATA = 1,
	GETFORMULA,
	GETENUMERATIONS,
	MAX_SELECTIONS
};

class Processor
{ 
public:
	virtual void execute() = 0;
};

/*
class Creator
{
public:
	Creator(int selectionId);
	virtual Processor* create() = 0;
};

template <class T>
class CreatorImpl : public Creator
{
public:
	CreatorImpl(int selectionId) : Creator(selectionId) {}
	virtual Processor* create() { return new T; }
};
*/
class GetDataProcessor : public Processor
{ 
public:
	virtual void execute();
private:
	static const bool isRegistered;
};

class GetFormulaProcessor : public Processor
{
public:
	virtual void execute();
private:
	static const bool isRegistered;
};

class GetEnumerationsProcessor : public Processor
{
public:
	virtual void execute();
private:
	static const bool isRegistered;
};

template <typename ID, typename CREATOR>
class Factory
{
private:
	typedef decltype(CREATOR()()) PROCESSOR;
public:
	PROCESSOR create(ID selectionId)
	{
		auto it = registry().find(selectionId);
		if (it != registry().end())
			return (it->second)();
		else
			return nullptr;
	}

	static bool Register(ID selectionId, CREATOR creator)
	{
		return registry().emplace(selectionId, creator).second;
	}

private:
	static std::unordered_map<ID, CREATOR>& registry()
	{
		static std::unordered_map<ID, CREATOR> _registry;
		return _registry;
	}
};

using PFactory = Factory<int, std::function<std::unique_ptr<Processor>()> >;

const bool GetDataProcessor::isRegistered 
	= PFactory::Register(GETDATA, []() { return std::unique_ptr<GetDataProcessor>(new GetDataProcessor); });
const bool GetFormulaProcessor::isRegistered
	= PFactory::Register(GETFORMULA, []() { return std::unique_ptr<GetFormulaProcessor>(new GetFormulaProcessor); });
const bool GetEnumerationsProcessor::isRegistered
	= PFactory::Register(GETENUMERATIONS, []() { return std::unique_ptr<GetEnumerationsProcessor>(new GetEnumerationsProcessor); });


PFactory factory;

/*
Creator::Creator(int selectionId)
{
	ProcessorFactory::Register(selectionId, this);
}
*/
void GetDataProcessor::execute()
{
	std::cout << "Execute GetData" << std::endl;
}

void GetFormulaProcessor::execute()
{
	std::cout << "Execute GetFormula" << std::endl;
}

void GetEnumerationsProcessor::execute()
{
	std::cout << "Execute GetEnumerations" << std::endl;
}

int main(int argc, char const *argv[])
{
	
	int selection;
	if(argc > 0)
	{
		selection = ::atoi(argv[1]);
	}

	auto p = factory.create(selection);

	if (p != nullptr)
		p->execute();
	else
		std::cerr << "Class not found!" << std::endl;

	return 0;
}


