#include "Property.hpp"
#include "DynArray.hpp"
#include <iostream>

class Test
{
public:
	Test(int x = 0)
	: X([this]() { return std::cref(this->x); },
		[this](int x) { return std::ref(this->x = x); }),
	 x(x)
	 {}
	
	Property<int> X;

private:
	int x;
};

int main()
{
	Test t{5};
	
	std::cout << t.X << '\n';
	t.X = 7;
	std::cout << t.X << '\n';

	DynArray<int> array;
	
	static_if(std::is_same<int, char>{}).then([&]()
	{
		std::cout << "true!\n";
	})
	.static_else_if(std::is_same<int, short>{}).then([&]()
	{
		std::cout << "else if true!\n";
	})
	.static_else([&]()
	{
		std::cout << "false!\n";
	});

	return 0;
}
