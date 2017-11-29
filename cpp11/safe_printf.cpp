/* safe printf */
#include <cstring>
#include <cstdio>
#include <type_traits>
#include <string>
#include <stdexcept>

using namespace std;

template <typename Integer>
	enable_if_t<is_integral<Integer>::value 
		&& is_signed<Integer>::value, long>
	normalizeArg(Integer arg) { return arg; }

template <typename Unsigned>
	enable_if_t<is_integral<Unsigned>::value 
		&& is_unsigned<Unsigned>::value, unsigned long>
	normalizeArg(Unsigned arg) { return arg; }

template <typename Floating>
	enable_if_t<is_floating_point<Floating>::value, double>
	normalizeArg(Floating arg) { return arg; }

template <typename Pointer>
	enable_if_t<is_pointer<Pointer>::value, Pointer>
	normalizeArg(Pointer arg) { return arg; }

const char * normalizeArg(const string& arg) { return arg.c_str(); }

void check_printf(const char *f)
{
	for(; *f; ++f)
	{
		if(*f != '%') continue;
		if(*++f == '%') continue;
		throw logic_error("Bad format - too few arguments");
	}
}

template <class T, typename... Ts>
void check_printf(const char *f, const T& t,
	const Ts&... ts)
{
	for (; *f; ++f)
	{
		if(*f != '%') continue;
		switch (*++f) 
		{
			case '%': continue;
			case 'f': case 'g':
				if(!is_floating_point<T>::value)
					throw logic_error("Bad format - not a float");
				break;
			case 's':
				break;
			case 'd': case 'i':
				if(!is_integral<T>::value || !is_signed<T>::value)
					throw logic_error("Bad format - not a signed int");
				break;
			case 'u':
				if(!is_integral<T>::value || !is_unsigned<T>::value)
					throw logic_error("Bad format - not an unsigned int");
				break;
			case 'p':
				if(!is_pointer<T>::value)
					throw logic_error("Bad format");
				break;
		}
		return check_printf(++f, ts...);
	}
	throw logic_error("Bad format - too many arguments");
}

template <typename... Ts>
int safe_printf(const char *f, const Ts&... ts)
{
#ifndef NDEBUG
	check_printf(f, normalizeArg(ts)... );
#endif
	return printf(f, normalizeArg(ts)... );
}

int main(int argc, char** argv)
{
	auto n = strlen(argv[1]);
	for (size_t i=0; i != 100000000; ++i)
	{
		safe_printf("Got argument %s of length %zu in iteration %zu\n", argv[1], n, i);
	}
	return 0;
}