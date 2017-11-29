#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

class Processor;
//class Creator;

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
};

class GetFormulaProcessor : public Processor
{
public:
	virtual void execute();
};

class GetEnumerationsProcessor : public Processor
{
public:
	virtual void execute();
};

template <typename CREATOR>
class ProcessorFactory
{
private:
	typedef decltype(CREATOR()()) PROCESSOR;
public:
	PROCESSOR create(int selectionId)
	{
		auto it = registry.find(selectionId);
		if (it != registry.end())
			return (it->second)();
		else
			return nullptr;
	}

	bool Register(int selectionId, CREATOR creator)
	{
		return registry.emplace(selectionId, creator).second;
	}

private:
	std::unordered_map<int, CREATOR> registry;

};

using PFactory = ProcessorFactory<std::function<std::unique_ptr<Processor>()> >;

//PFactory factory;

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
	PFactory factory;
	factory.Register(GETDATA, []() { return std::unique_ptr<GetDataProcessor>(new GetDataProcessor); });
	factory.Register(GETFORMULA, []() { return std::unique_ptr<GetFormulaProcessor>(new GetFormulaProcessor); });
	factory.Register(GETENUMERATIONS, []() { return std::unique_ptr<GetEnumerationsProcessor>(new GetEnumerationsProcessor); });

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


