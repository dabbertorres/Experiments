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

	return 0;
}
