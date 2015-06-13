#include "Property.hpp"

class Test
{
	public:
		Test(int t)
		:	x(t),
			X(x)
		{}
		
		swift::Property<int> X;
		
	private:
		int x;
};

int main()
{
	Test test(5);
	
	test.X = 7;
	
	test.X();
	
	return 0;
}