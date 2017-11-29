/* exception handling atoi */
#include <boost/variant.hpp>
#include <exception>
#include <iostream>

using namespace std;
using boost::get;

enum class Invalid{};


template <typename T> class Expected {
public:
	Expected() { data_ = T(); }
	Expected(const T& v) : data_(v) {}
	
	template <typename E>
		Expected(const E& obj, Invalid)
	{
		data_ = make_exception_ptr(obj);
	}

	bool valid() const
	{
		return (data_.type() == typeid(T));
	}

	operator T&()
	{
		if(valid())
			return boost::get<T>(data_);
		else
			rethrow_exception(get<exception_ptr>(data_));
	}
	operator const T&() const
	{
		if(valid())
			return boost::get<T>(data_);
		else
			rethrow_exception(get<exception_ptr>(data_));
	}

	exception_ptr getExceptionPtr() const
	{
		return boost::get<exception_ptr>(data_);
	}

private:
	boost::variant<T, exception_ptr> data_;
};



int main (int argc, char** argv)
{
	/* ... code ... */
	auto goodInt = Expected<int>(15);
	assert (int(goodInt) == 15);
	cout << goodInt << endl;
	auto goodDub = Expected<double>(100.0);
	assert (double(goodDub) == 100.0);
	cout << goodDub << endl;
	
	// Invalid disambiguates bad case
	auto bad = Expected<int>(std::runtime_error("I'm an exception!"), Invalid());
	assert(!bad.valid());
	try {
		cout << bad << endl;
	}
	catch (std::runtime_error & e)
	{
		cout << e.what() << endl;
	}
	return 0;
}