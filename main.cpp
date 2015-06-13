#include "Property.hpp"
#include <iostream>

class Test
{
	public:
		Test(int t)
		:	X(x),
			x(t)
		{}

		swift::Property<int> X;

	private:
		int x;
};

int main()
{
	Test test(5);

	std::cout << "X: " << test.X() << '\n';

	test.X = 7;

	std::cout << "X: " << test.X() << '\n';

	return 0;
}
