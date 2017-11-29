#include <iostream>
#include <unordered_map>

class Processor;
class ProcessorFactory;
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

class GetDataProcessor : public Processor
{ 
public:
	virtual void execute();
private:
	static const CreatorImpl<GetDataProcessor> creator;
};

class GetFormulaProcessor : public Processor
{
public:
	virtual void execute();
private:
	static const CreatorImpl<GetFormulaProcessor> creator;
};

class GetEnumerationsProcessor : public Processor
{
public:
	virtual void execute();
private:
	static const CreatorImpl<GetEnumerationsProcessor> creator;
};

class ProcessorFactory
{
public:
	static Processor* create(int selectionId);
	static void Register(int selectionId, Creator* creator);
private:
	static std::unordered_map<int, Creator*>& registry();
};

const CreatorImpl<GetDataProcessor> GetDataProcessor::creator(GETDATA);
const CreatorImpl<GetFormulaProcessor> GetFormulaProcessor::creator(GETFORMULA);
const CreatorImpl<GetEnumerationsProcessor> GetEnumerationsProcessor::creator(GETENUMERATIONS);


ProcessorFactory factory;

Creator::Creator(int selectionId)
{
	ProcessorFactory::Register(selectionId, this);
}

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

void ProcessorFactory::Register(int selectionId, Creator* creator)
{
	registry()[selectionId] = creator;
}

Processor* ProcessorFactory::create(int selectionId)
{
	auto it = registry().find(selectionId);
	if (it != registry().end())
		return it->second->create();
	else
		return nullptr;
}

std::unordered_map<int, Creator*>& ProcessorFactory::registry()
{
	static std::unordered_map<int, Creator*> _registry;
	return _registry;
}

int main(int argc, char const *argv[])
{
	
	int selection;
	if(argc > 0)
	{
		selection = ::atoi(argv[1]);
	}

	Processor* p;
	p = factory.create(selection);

	if (p != nullptr)
		p->execute();
	else
		std::cerr << "Class not found!" << std::endl;

	return 0;
}


