#include "Property.hpp"
#include "DynArray.hpp"
#include <iostream>

class Test
{
	public:
		Test(int t)
		:	X(	[this]() -> const int&
				{
					return this->x;
				},
				[this](int t) -> int&
				{
					this->x = t;
					return this->x;
				}),
			x(t)
		{}

		Property<int> X;

	private:
		int x;
};

int main()
{
	Test test(5);

	std::cout << "X: " << test.X() << '\n';

	test.X = 7;

	std::cout << "X: " << test.X() << '\n';

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
